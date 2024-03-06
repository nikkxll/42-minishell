/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnikifor <dnikifor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 16:08:57 by dnikifor          #+#    #+#             */
/*   Updated: 2024/03/06 11:11:05 by dnikifor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

char	**edit_env_list(char **envp, char *new_var, int position)
{
	envp[position] = ft_strdup(new_var);	
	return (envp);
}

char	**add_to_env_list(char **res, char **arr, char **envp, int *operations)
{
	int		i;
	int		j;
	int		len;
	
	i = 0;
	j = -1;
	while (operations[++j])
	{
		if (operations[j] == 3)
			i++;
	}
	len = ft_arrlen((void **)envp);
	res = (char **)ft_calloc(len + i + 1, sizeof(char *));
	if (res == NULL)
		return (NULL);
	ft_memcpy((void *)res, (void *)envp, sizeof(char *) * len);
	j = -1;
	i = 0;
	while (operations[++j])
	{
		if (operations[j] == 3)
			res[len + i++] = ft_strdup(arr[j]);
	}
	return (res);
}

int	arg_var(char **arr, char *var, int i, int j)
{
	while (--i >= 0)
	{
		if (ft_strncmp(arr[i], var, j) == 0)
			return (i) ;
	}
	return (-1);
}

// 1 - error, 2 - edit, 3 - add, 4 - skip
int check_operation(char **arr, char **envp, int *operations)
{
	int	i;
	int	j;
	
	i = -1;
	j = 0;
	while (arr[++i] != NULL)
	{
		j = 0;
		while (arr[i][j] != EQUAL_SIGN && arr[i][j] != NULL_TERM
				&& arr[i][j] != SPACE && !ft_isdigit(arr[i][j]))
				j++;
		if ((arr[i][j] == SPACE) || (ft_isdigit(arr[i][j]) && j == 0))
			operations[i] = 1;
		else if (arr[i][j] == EQUAL_SIGN)
		{
			if (env_var(envp, arr[i], -1, j) != -1
				|| arg_var(arr, arr[i], i, j) != -1)
				operations[i] = 2;
			else
				operations[i] = 3;
		}
		else
			operations[i] = 4;
	}
	return (0);
}

char	**execute_export(char **res, char **arr, char **envp, int *operations)
{
	res = add_to_env_list(res, arr, envp, operations);
	// execute_edit(res, arr, envp, operations);
	// execute_error(res, arr, envp, operations);
	return (res);
}

int	export_with_args(char **arr, char **envp, int i)
{
	char	**res;
	int		*operations;

	operations = ft_calloc(ft_arrlen((void **)arr) + 1, sizeof(int));
	if (!operations)
		return (-1);
	check_operation(arr, envp, operations);
	res = execute_export(res, arr, envp, operations);
	int k = -1;
	while(res[++k])
		printf("%s\n", res[k]);
	return (1);
}

int	run_export(char **arr, char **envp)
{
	int	arr_len;

	arr_len = ft_arrlen((void **)arr);
	if (arr_len > 0)
		export_with_args(arr, envp, 0);
	return (1);
}
