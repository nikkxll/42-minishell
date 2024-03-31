/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnikifor <dnikifor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 15:50:24 by dnikifor          #+#    #+#             */
/*   Updated: 2024/04/01 01:41:22 by dnikifor         ###   ########.fr       */
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
	if (!ft_strncmp("echo", arr[0], ECHO_LEN))
		return (run_echo(arr + 1, 0, 0, 0));
	else if (!ft_strncmp("cd", arr[0], CD_LEN))
		return (run_cd(arr + 1, *envp));
	else if (!ft_strncmp("pwd", arr[0], PWD_LEN))
		return (run_pwd(arr + 1));
	else if (!ft_strncmp("export", arr[0], EXPORT_LEN))
		return (run_export(arr + 1, envp));
	else if (!ft_strncmp("unset", arr[0], UNSET_LEN))
		return (run_unset(arr + 1, envp));
	else if (!ft_strncmp("env", arr[0], ENV_LEN))
		return (run_env(arr + 1, envp));
	else if (!ft_strncmp("exit", arr[0], EXIT_LEN))
		return (run_exit(arr + 1));
	else
	{
		printf("EXECVE: |%s|\n", arr[0]);
		return (1);
	}
}
