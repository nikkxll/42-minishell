/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnikifor <dnikifor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 16:08:57 by dnikifor          #+#    #+#             */
/*   Updated: 2024/03/05 23:21:02 by dnikifor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

int errors_check(char **arr, int *i, int *j)
{
	if ((arr[*i][*j] == SPACE) || (ft_isdigit(arr[*i][*j]) && *j == 0))
	{
		print_error_with_arg("not a valid identifier\n", arr[*i],
			"export: `");
		(*i)++;
		return (1);
	}
	return (0);
}

char	**add_to_env_list(char **envp, char *new_var)
{
	int		i;
	char	**res;
	int		len;

	len = ft_arrlen((void **)envp);
	res = (char **)ft_calloc(len + 2, sizeof(char *));
	if (res == NULL)
		return (NULL);
	ft_memcpy((void *)res, (void *)envp, sizeof(char *) * len);
	res[len] = ft_strdup(new_var);
	envp = res;
	return (res);
}

char	**edit_env_list(char **envp, char *new_var, int position)
{
	envp[position] = ft_strdup(new_var);	
	return (envp);
}

int	export_with_args(char **arr, char **envp, int i)
{
	int		j;
	char	**res;
	int		env_var_check;
	
	while (arr[i] != NULL)
	{
		j = 0;
		while (arr[i][j] != '=' && arr[i][j] != NULL_TERM
			&& arr[i][j] != SPACE && !ft_isdigit(arr[i][j]))
			j++;
		if (errors_check(arr, &i, &j))
			continue;
		if (arr[i][j] == '=')
		{
			env_var_check = env_var(envp, arr[i], -1, j);
			if (env_var_check == -1)
				res = add_to_env_list(envp, arr[i]);
			else
				envp = edit_env_list(envp, arr[i], env_var_check);
			i++;
			continue ;
		}
		else
		{
			i++;
			continue ;
		}
	}
	int k = -1;
	while (res[++k])
		ft_printf("%s\n", res[k]);
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
