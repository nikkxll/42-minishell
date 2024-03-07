/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnikifor <dnikifor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 15:50:24 by dnikifor          #+#    #+#             */
/*   Updated: 2024/03/07 19:50:24 by dnikifor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

int	command_run(char **arr, char **envp)
{
	if (!ft_strncmp("echo", arr[0], ft_strlen(arr[0])))
		return (run_echo(arr + 1, 0, 0, 0));
	else if (!ft_strncmp("cd", arr[0], ft_strlen(arr[0])))
		return (run_cd(arr + 1, envp));
	else if (!ft_strncmp("pwd", arr[0], ft_strlen(arr[0])))
		return (run_pwd(arr + 1));
	else if (!ft_strncmp("export", arr[0], ft_strlen(arr[0])))
		return (run_export(arr + 1, &envp));
	else if (!ft_strncmp("unset", arr[0], ft_strlen(arr[0])))
		return (run_unset(arr + 1, &envp));
	else if (!ft_strncmp("env", arr[0], ft_strlen(arr[0])))
		return (run_env(arr + 1, &envp));
	// else if (!ft_strncmp("exit", arr[0], ft_strlen(arr[0])))
	// 	return (run_exit(arr, 1, 0));
	else
		return (1);
}

// int	main(int ac, char **av, char **envp)
// {
// 	int		status;
// 	char	**arr;
// 	char	**env;
// 	int		i;

// 	i = 0;
// 	arr = ft_calloc(ac, sizeof(char *));
// 	env = cpy_env(envp);
// 	while (i < ac - 1)
// 	{
// 		arr[i] = ft_calloc(ft_strlen(av[i + 1]) + 1, sizeof(char));
// 		ft_memcpy(arr[i], av[i + 1], ft_strlen(av[i + 1]));
// 		i++;
// 	}
// 	arr[i] = NULL;
// 	processing(arr, 0);
// 	status = command_run(arr, env);
// 	if (status == MALLOC_ERR)
// 		printf("%s\n", "malloc error");
// 	ft_free_2d_array(arr);
// 	ft_free_2d_array(env);
// 	return (0);
// }
