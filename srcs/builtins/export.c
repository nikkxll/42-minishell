/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnikifor <dnikifor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 16:08:57 by dnikifor          #+#    #+#             */
/*   Updated: 2024/03/07 19:50:58 by dnikifor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

static int	execute_export(char **new_env, char **arr, char **envp,
	int *operations)
{
	if (add_to_env_list(&new_env, arr, envp, operations) == MALLOC_ERR)
		return (MALLOC_ERR);
	if (edit_env_list(&new_env, arr, operations) == MALLOC_ERR)
		return (MALLOC_ERR);
	execute_error(arr, operations);
	return (SUCCESS);
}

static int	export_with_args(char **arr, char ***envp)
{
	char	**new_env;
	char	**env;
	int		*operations;

	env = *envp;
	new_env = NULL;
	operations = ft_calloc(ft_arrlen((void **)arr) + 1, sizeof(int));
	if (!operations)
		return (MALLOC_ERR);
	create_operations_array(arr, env, operations);
	if (execute_export(new_env, arr, env, operations) == MALLOC_ERR)
	{
		free(operations);
		return (MALLOC_ERR);
	}
	*envp = new_env;
	free(operations);
	return (SUCCESS);
}

static int	export_without_args(char ***envp, int i, int j)
{
	char	**envp_sorted;

	envp_sorted = sort_string_arr(*envp, ft_arrlen((void **)*envp));
	if (!envp_sorted)
		return (MALLOC_ERR);
	while (envp_sorted[++i])
	{
		j = 0;
		if (envp_sorted[i][0] == UNSCORE && envp_sorted[i][1] == EQUAL)
			continue ;
		ft_putstr_fd("declare -x ", 1);
		while (envp_sorted[i][j] != EQUAL)
			ft_putchar_fd(envp_sorted[i][j++], 1);
		ft_putchar_fd(EQUAL, 1);
		ft_putchar_fd(D_QUOTE, 1);
		j++;
		ft_putstr_fd(envp_sorted[i] + j, 1);
		ft_putchar_fd(D_QUOTE, 1);
		ft_putchar_fd(NL, 1);
	}
	free(envp_sorted);
	return (SUCCESS);
}

int	run_export(char **arr, char ***envp)
{
	int		arr_len;

	arr_len = ft_arrlen((void **)arr);
	if (arr_len >= 1 && ft_strlen(arr[0]) > 1 && arr[0][0] == DASH)
	{
		arr[0][2] = NULL_TERM;
		print_error_with_arg("options not supported\n", arr[0], "env: ");
		return (SUCCESS);
	}
	else if (arr_len > 0)
	{
		if (export_with_args(arr, envp) == MALLOC_ERR)
			return (MALLOC_ERR);
	}
	else
	{
		if (export_without_args(envp, -1, 0) == MALLOC_ERR)
			return (MALLOC_ERR);
	}
	return (SUCCESS);
}
