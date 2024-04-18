/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnikifor <dnikifor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 15:50:24 by dnikifor          #+#    #+#             */
/*   Updated: 2024/04/19 00:05:15 by dnikifor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

static void	run_nothing(char **arr, t_minishell *ms);

/**
 * @brief	A function that runs either built-in command or calling execution
 * module to run execve
 * @param	arr array of arguments or options if allowed
 * @param	ms pointer to the common project @c `t_minishell` structure
 * @param	cmd_type command type
 * @return	execution exit status
 */
int	command_run(char **arr, t_minishell *ms, int cmd_type)
{
	if (cmd_type == C_EMPTY || cmd_type == C_BLANK)
		run_nothing(arr, ms);
	else if (cmd_type == C_ECHO)
	{
		run_echo(arr + 1, 0, 0, 0);
		ms->exit_status = SUCCESS;
	}
	else
	{
		ms->exit_status = SUCCESS;
		if (cmd_type == C_CD)
			run_cd(arr + 1, ms, 0);
		else if (cmd_type == C_PWD)
			run_pwd(arr + 1, ms);
		else if (cmd_type == C_EXPORT)
			run_export(arr + 1, ms);
		else if (cmd_type == C_UNSET)
			run_unset(arr + 1, ms);
		else if (cmd_type == C_ENV)
			run_env(arr + 1, ms);
		else if (cmd_type == C_EXIT)
			run_exit(arr + 1, ms, 0);
	}
	return (ms->exit_status);
}

/**
 * @brief	Execute a no-operation command
 * @note	This function serves as a placeholder for executing a command
 * that does nothing. It sets the exit status to @c `CMD_NF_FAILURE` and
 * prints an error message indicating that the command was not found.
 * @param	arr An array of strings representing the command and its arguments
 * @param	ms  A pointer to the minishell structure
 * @return	@c `void`
 */
static void	run_nothing(char **arr, t_minishell *ms)
{
	if (*arr == NULL)
		return ;
	ms->exit_status = CMD_NF_FAILURE;
	print_err_msg(*arr, ": command not found\n");
}
