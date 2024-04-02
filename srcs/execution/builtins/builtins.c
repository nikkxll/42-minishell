/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dshatilo <dshatilo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 15:50:24 by dnikifor          #+#    #+#             */
/*   Updated: 2024/04/02 11:30:59 by dshatilo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../headers/minishell.h"

/**
 * @brief	A function that runs either built-in command or calling execution
 * module to run execve
 * @param	arr array of arguments or options if allowed
 * @param	envp pointer to the environment array
 * @return	execution exit status
 */
int	command_run(char **arr, t_minishell *ms)
{
	if (!ft_strncmp("echo", arr[0], ECHO_LEN))
	{
		run_echo(arr + 1, 0, 0, 0);
		ms->exit_status = SUCCESS;
	}
	else if (!ft_strncmp("cd", arr[0], CD_LEN))
		run_cd(arr + 1, ms);
	else if (!ft_strncmp("pwd", arr[0], PWD_LEN))
		run_pwd(arr + 1, ms);
	else if (!ft_strncmp("export", arr[0], EXPORT_LEN))
		run_export(arr + 1, ms);
	else if (!ft_strncmp("unset", arr[0], UNSET_LEN))
		run_unset(arr + 1, ms);
	else if (!ft_strncmp("env", arr[0], ENV_LEN))
		run_env(arr + 1, ms);
	else if (!ft_strncmp("exit", arr[0], EXIT_LEN))
		run_exit(arr + 1, ms);
	else
		printf("EXECVE: |%s|\n", arr[0]);
	return (ms->exit_status);
}
