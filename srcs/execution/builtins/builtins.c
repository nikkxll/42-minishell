/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dshatilo <dshatilo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 15:50:24 by dnikifor          #+#    #+#             */
/*   Updated: 2024/04/02 19:19:16 by dnikifor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../headers/minishell.h"

/**
 * @brief	A function that runs either built-in command or calling execution
 * module to run execve
 * @param	arr array of arguments or options if allowed
 * @param	ms pointer to the common project @c `t_minishell` structure
 * @return	execution exit status
 */
int	command_run(char **arr, t_minishell *ms)
{
	ms->exit_status = SUCCESS;
	if (ft_strncmp(arr[0], "echo", ECHO_LEN) == 0)
		run_echo(arr + 1, 0, 0, 0);
	else if (ft_strncmp(arr[0], "cd", CD_LEN) == 0)
		run_cd(arr + 1, ms, 0);
	else if (ft_strncmp(arr[0], "pwd", PWD_LEN) == 0)
		run_pwd(arr + 1, ms);
	else if (ft_strncmp(arr[0], "export", EXPORT_LEN) == 0)
		run_export(arr + 1, ms);
	else if (ft_strncmp(arr[0], "unset", UNSET_LEN) == 0)
		run_unset(arr + 1, ms);
	else if (ft_strncmp(arr[0], "env", ENV_LEN) == 0)
		run_env(arr + 1, ms);
	else if (ft_strncmp(arr[0], "exit", EXIT_LEN) == 0)
		run_exit(arr + 1, ms);
	return (ms->exit_status);
}
