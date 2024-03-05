/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnikifor <dnikifor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 15:50:24 by dnikifor          #+#    #+#             */
/*   Updated: 2024/03/04 19:26:39 by dnikifor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

int	command_run(char **arr, char **envp)
{
	if (!ft_strncmp("echo", arr[0], ft_strlen(arr[0])))
		return (run_echo(arr, 1, 0, 0));
	else if (!ft_strncmp("cd", arr[0], ft_strlen(arr[0])))
		return (run_cd(arr, envp));
	// else if (!ft_strncmp("pwd ", str, 4))
	// 	run_pwd(str + 4);
	// else if (!ft_strncmp("export ", str, 7))
	// 	run_export(str + 7);
	// else if (!ft_strncmp("unset ", str, 6))
	// 	run_unset(str + 6);
	// else if (!ft_strncmp("env ", str, 4))
	// 	run_env(str + 4);
	// else if (!ft_strncmp("exit", arr[0], ft_strlen(arr[0])))
	// 	return (run_exit(arr, 1, 0));
	else
		return (0);
}

int	main(int ac, char **av, char **envp)
{
	int		status;
	char	**arr;

	arr = av + 1;
	preprocessing(arr, 0);
	status = command_run(arr, envp);
	if (status == 0)
		printf("%s\n", "builtin haven't been found");
	else if (status == -1)
		printf("%s\n", "error occured");
	return (0);
}
