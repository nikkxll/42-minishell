/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnikifor <dnikifor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 11:53:09 by dnikifor          #+#    #+#             */
/*   Updated: 2024/03/27 23:24:50 by dnikifor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"
#include <readline/readline.h>
#include <readline/history.h>

int	main(void)
{
	char		*command;
	extern char	**environ;
	char		**arr;
	char		**env;

	env = cpy_env(environ);
	while (1)
	{
		command = readline("\033[1;36mlitbash-1.0.0\033[0m $ ");
		if (!command)
		{
			printf("\n");
			exit (0);
		}
		if (command && *command)
			add_history(command);
		else
			continue;
		arr = wrapper_ft_split_with_quotes(command);
		minishell(arr, &env);
	}
	rl_clear_history();
	ft_free_2d_array(env);
	return (0);
}

// int	main(void)
// {
// 	char		*command;
// 	extern char	**environ;
// 	char		**arr;
// 	char		**env;

// 	env = cpy_env(environ);
// 	command = ft_strdup("echo a*b");
// 	// while (1)
// 	// {
// 	// 	command = readline("e-bash > ");
// 	// 	if (!command)
// 	// 	{
// 	// 		printf("\n");
// 	// 		break ;
// 	// 	}
// 	// 	if (command && *command)
// 	// 		add_history(command);
// 		arr = wrapper_ft_split_with_quotes(command);
// 		minishell(arr, &env);
// 	// }
// 	// rl_clear_history();
// 	ft_free_2d_array(env);
// 	return (0);
// }
