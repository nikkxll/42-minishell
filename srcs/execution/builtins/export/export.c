/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnikifor <dnikifor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 16:08:57 by dnikifor          #+#    #+#             */
/*   Updated: 2024/04/01 01:41:13 by dnikifor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../headers/minishell.h"

/**
 * @brief	A function that executes different possible export operations
 * @param	new_env pointer to the new environment array
 * @param	arr array of arguments or options if allowed
 * @param	envp pointer to the environment array
 * @param	operations auxiliary array to calculate the number of operations
 * of different type
 * @return	@c `MALLOC_ERR` if malloc failure occured, @c `SUCCESS` otherwise
 */
static int	execute_export(char ***new_env, char **arr, char ***envp,
	int *operations)
{
	if (add_to_env_list(new_env, arr, *envp, operations) == MALLOC_ERR)
		return (MALLOC_ERR);
	if (*new_env)
	{
		if (edit_env_list(new_env, arr, operations) == MALLOC_ERR)
			return (MALLOC_ERR);
	}
	else
	{
		if (edit_env_list(envp, arr, operations) == MALLOC_ERR)
			return (MALLOC_ERR);
	}
	execute_error(arr, operations);
	return (SUCCESS);
}

/**
 * @brief	A function that runs export with arguments
 * @param	arr array of arguments or options if allowed
 * @param	envp pointer to the environment array
 * @return	@c `MALLOC_ERR` if malloc failure occured, @c `SUCCESS` otherwise
 */
static int	export_with_args(char **arr, char ***envp)
{
	char	**new_env;
	int		*operations;

	new_env = NULL;
	operations = ft_calloc(ft_arrlen((void **)arr) + 1, sizeof(int));
	if (!operations)
		return (MALLOC_ERR);
	create_operations_array(arr, *envp, operations);
	if (execute_export(&new_env, arr, envp, operations) == MALLOC_ERR)
	{
		free(operations);
		return (MALLOC_ERR);
	}
	if (new_env)
		*envp = new_env;
	free(operations);
	return (SUCCESS);
}

/**
 * @brief	A function that runs export without arguments
 * @param	envp pointer to the environment array
 * @param	i index
 * @param	j index
 * @return	@c `MALLOC_ERR` if malloc failure occured, @c `SUCCESS` otherwise
 */
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
		ft_putstr_fd("declare -x ", STDOUT_FILENO);
		while (envp_sorted[i][j] != EQUAL && envp_sorted[i][j] != NULL_TERM)
			ft_putchar_fd(envp_sorted[i][j++], STDOUT_FILENO);
		ft_putchar_fd(EQUAL, STDOUT_FILENO);
		ft_putchar_fd(D_QUOTE, STDOUT_FILENO);
		j++;
		ft_putstr_fd(envp_sorted[i] + j, STDOUT_FILENO);
		ft_putchar_fd(D_QUOTE, STDOUT_FILENO);
		ft_putchar_fd(NL, STDOUT_FILENO);
	}
	free(envp_sorted);
	return (SUCCESS);
}

/**
 * @brief	A function that runs export built-in command
 * @param	arr array of arguments or options if allowed
 * @param	envp pointer to the environment array
 * @return	@c `MALLOC_ERR` if malloc failure occured, @c `SUCCESS` otherwise
 */
int	run_export(char **arr, char ***envp)
{
	int		arr_len;

	arr_len = ft_arrlen((void **)arr);
	if (arr_len >= 1 && ft_strlen(arr[0]) > 1 && arr[0][0] == DASH)
	{
		arr[0][2] = NULL_TERM;
		print_arg_err_msg("env: `", arr[0], "': options are not supported\n");
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
