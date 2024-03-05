/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnikifor <dnikifor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 15:50:24 by dnikifor          #+#    #+#             */
/*   Updated: 2024/03/05 19:24:48 by dnikifor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

int	command_run(char **arr, char **envp)
{
	if (!ft_strncmp("echo", arr[0], ft_strlen(arr[0])))
		return (run_echo(arr + 1, 1, 0, 0));
	else if (!ft_strncmp("cd", arr[0], ft_strlen(arr[0])))
		return (run_cd(arr + 1, envp));
	else if (!ft_strncmp("pwd", arr[0], ft_strlen(arr[0])))
		return (run_pwd(arr + 1));
	else if (!ft_strncmp("export", arr[0], ft_strlen(arr[0])))
		return (run_export(arr + 1, envp));
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
	int		i;

	i = 0;
	arr = ft_calloc(ac, sizeof(char *));
	while (i < ac - 1)
	{
		arr[i] = malloc(sizeof(char) * ft_strlen(av[i + 1]));
		ft_memcpy(arr[i], av[i + 1], ft_strlen(av[i + 1]));
		i++;
	}
	arr[i] = NULL;
	processing(arr, 0);
	status = command_run(arr, envp);
	if (status == 0)
		printf("%s\n", "builtin haven't been found");
	else if (status == -1)
		printf("%s\n", "error occured");
	return (0);
}
