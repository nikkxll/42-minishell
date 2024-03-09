/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnikifor <dnikifor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 15:50:24 by dnikifor          #+#    #+#             */
/*   Updated: 2024/03/10 01:02:45 by dnikifor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

int	command_run(char **arr, char ***envp)
{
	if (!ft_strncmp("echo", arr[0], ft_strlen(arr[0])))
		return (run_echo(arr + 1, 0, 0, 0));
	else if (!ft_strncmp("cd", arr[0], ft_strlen(arr[0])))
		return (run_cd(arr + 1, *envp));
	else if (!ft_strncmp("pwd", arr[0], ft_strlen(arr[0])))
		return (run_pwd(arr + 1));
	else if (!ft_strncmp("export", arr[0], ft_strlen(arr[0])))
		return (run_export(arr + 1, envp));
	else if (!ft_strncmp("unset", arr[0], ft_strlen(arr[0])))
		return (run_unset(arr + 1, envp));
	else if (!ft_strncmp("env", arr[0], ft_strlen(arr[0])))
		return (run_env(arr + 1, envp));
	// else if (!ft_strncmp("exit", arr[0], ft_strlen(arr[0])))
	// 	return (run_exit(arr, 1, 0));
	else
	{
		printf("EXECVE: |%s|\n", arr[0]);
		return (1);
	}
}
