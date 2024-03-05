/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnikifor <dnikifor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 16:08:57 by dnikifor          #+#    #+#             */
/*   Updated: 2024/03/05 19:45:32 by dnikifor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

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
	res[len] = new_var;
	return (res);
}

int	export_with_args(char **arr, char **envp, int i)
{
	int		j;
	char	**res;

	while (arr[i] != NULL)
	{
		j = 0;
		while (arr[i][j] != '=' && arr[i][j] != NULL_TERM
			&& arr[i][j] != SPACE && !ft_isdigit(arr[i][j]))
			j++;
		if (arr[i][j] == SPACE)
		{
			print_error_with_arg("not a valid identifier\n", arr[i],
				"export: `");
			i++;
			continue ;
		}
		if (arr[i][j] == '=')
		{
			res = add_to_env_list(envp, arr[i]);
			i++;
			continue ;
		}
		if (ft_isdigit(arr[i][j]) && j == 0)
		{
			print_error_with_arg("not a valid identifier\n", arr[i],
				"export: `");
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
