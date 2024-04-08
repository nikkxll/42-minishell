/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnikifor <dnikifor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 15:50:24 by dnikifor          #+#    #+#             */
/*   Updated: 2024/04/08 12:37:19 by dnikifor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

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
	if (arr[0] == NULL)
		return (0);
	if (cmd_type == ECHO)
	{
		run_echo(arr + 1, 0, 0, 0);
		ms->exit_status = SUCCESS;
	}
	else
	{
		ms->exit_status = SUCCESS;
		if (cmd_type == CD)
			run_cd(arr + 1, ms, 0);
		else if (cmd_type == PWD)
			run_pwd(arr + 1, ms);
		else if (cmd_type == EXPORT)
			run_export(arr + 1, ms);
		else if (cmd_type == UNSET)
			run_unset(arr + 1, ms);
		else if (cmd_type == ENV)
			run_env(arr + 1, ms);
		else if (cmd_type == EXIT)
			run_exit(arr + 1, ms, 0);
	}
	return (ms->exit_status);
}
