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
int	command_run(char **arr, char ***envp)
{
	if (ft_strncmp(arr[0], "echo", ECHO_LEN) == 0)
		return (run_echo(arr + 1, 0, 0, 0));
	if (ft_strncmp(arr[0], "cd", CD_LEN) == 0)
		return (run_cd(arr + 1, *envp));
	if (ft_strncmp(arr[0], "pwd", PWD_LEN) == 0)
		return (run_pwd(arr + 1));
	if (ft_strncmp(arr[0], "export", EXPORT_LEN) == 0)
		return (run_export(arr + 1, envp));
	if (ft_strncmp(arr[0], "unset", UNSET_LEN) == 0)
		return (run_unset(arr + 1, envp));
	if (ft_strncmp(arr[0], "env", ENV_LEN) == 0)
		return (run_env(arr + 1, envp));
	if (ft_strncmp(arr[0], "exit", ENV_LEN) == 0)
		return (run_exit(arr + 1));
	return (0);
}
