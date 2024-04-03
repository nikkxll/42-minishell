/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnikifor <dnikifor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 16:08:57 by dnikifor          #+#    #+#             */
/*   Updated: 2024/04/03 20:22:10 by dnikifor         ###   ########.fr       */
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
 * @return	@c `MALLOC_ERR` if malloc failure occured,
 * @c `GENERIC_ERROR` if generic type of error occured
 * @c `SUCCESS` otherwise
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
	if (execute_error(arr, operations))
		return (GENERIC_ERROR);
	return (SUCCESS);
}

/**
 * @brief	A function that runs export with arguments
 * @param	arr array of arguments or options if allowed
 * @param	ms pointer to the common project @c `t_minishell` structure
 * @return	@c `void`
 */
static void	export_with_args(char **arr, t_minishell *ms)
{
	char	**new_env;
	int		*operations;

	new_env = NULL;
	operations = ft_calloc(ft_arrlen((void **)arr) + 1, sizeof(int));
	if (!operations)
	{
		ms->exit_status = MALLOC_ERR;
		return ;
	}
	create_operations_array(arr, ms->env, operations);
	ms->exit_status = execute_export(&new_env, arr, &(ms->env), operations);
	if (ms->exit_status == MALLOC_ERR)
	{
		free(operations);
		return ;
	}
	if (new_env)
		ms->env = new_env;
	free(operations);
}

/**
 * @brief	A function that runs export without arguments
 * @param	ms pointer to the common project @c `t_minishell` structure
 * @param	i index
 * @param	j index
 * @return	@c `void`
 */
static void	export_without_args(t_minishell *ms, int i, int j)
{
	char	**envp_sorted;

	envp_sorted = sort_string_arr(ms->env, ft_arrlen((void **)ms->env));
	if (!envp_sorted)
	{
		ms->exit_status = MALLOC_ERR;
		return ;
	}
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
}

/**
 * @brief	A function that runs export built-in command
 * @param	arr array of arguments or options if allowed
 * @param	ms pointer to the common project @c `t_minishell` structure
 * @return	@c `void`
 */
void	run_export(char **arr, t_minishell *ms)
{
	int		arr_len;

	arr_len = ft_arrlen((void **)arr);
	if (arr_len > 0 && ft_strlen(arr[0]) > 1 && arr[0][0] == DASH)
	{
		arr[0][2] = NULL_TERM;
		print_arg_err_msg("env: `", arr[0], "': options are not supported\n");
		ms->exit_status = CMD_ARG_ERROR;
	}
	else if (arr_len > 0)
		export_with_args(arr, ms);
	else
		export_without_args(ms, -1, 0);
}
