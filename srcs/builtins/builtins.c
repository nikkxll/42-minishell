/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnikifor <dnikifor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 15:50:24 by dnikifor          #+#    #+#             */
/*   Updated: 2024/03/12 14:06:37 by dnikifor         ###   ########.fr       */
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

// int	main(int ac, char **av, char **envp)
// {
// 	char	**arr;
// 	char	**env;
// 	int		i;

// 	i = 0;
// 	arr = wrapper_ft_split_with_quotes(av[1]);
// 	env = cpy_env(envp);
// 	while (arr[i])
// 	{
// 		if (expand_dollar_sign(&arr[i++], env, 0) == MALLOC_ERR)
// 			printf("%s\n", "malloc error");
// 	}
// 	processing(arr, 0);
// 	if (command_run(arr, &env) == MALLOC_ERR)
// 		printf("%s\n", "malloc error");

// 	printf("\n\n\n\n\n");
// 	int k = -1;
// 	while (env[++k])
// 		printf("%s\n", env[k]);

// 	ft_free_2d_array(arr);
// 	ft_free_2d_array(env);
// 	return (0);
// }
