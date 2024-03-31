/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnikifor <dnikifor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 15:09:34 by dshatilo          #+#    #+#             */
/*   Updated: 2024/04/01 02:04:46 by dnikifor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

int	minishell(char **arr, char ***env)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		if (expand_dollar_sign(&arr[i++], *env, 0) == MALLOC_ERR)
			printf("%s\n", "malloc error");
	}
	if (array_build_before_wc(&arr, -1, -1, -1) == MALLOC_ERR)
		printf("%s\n", "malloc error");
	if (wildcards(&arr) != 0)
	{
		printf("%s\n", "error occured");
		return (0);
	}
	processing(arr, 0);
	if (command_run(arr, env) == MALLOC_ERR)
		printf("%s\n", "malloc error");
	ft_free_2d_array(arr);
	return (0);
}

int	main(void)
{
	char		*command;
	extern char	**environ;
	char		**arr;
	char		*folder_name;
	char		*prompt;
	t_minishell	ms;

	ms.env = cpy_env(environ);
	ms.exit_status = pwd_init(&ms.env);
	if (ms.exit_status != 0)
		return (ms.exit_status);
	ms.exit_status = shlvl_init(&ms.env);
	if (ms.exit_status != 0)
		return (ms.exit_status);
	while (1)
	{
		get_current_folder_name(&folder_name);
		get_prompt(folder_name, &prompt);
		command = readline(prompt);
		if (is_blank_string(command))
			continue ;
		if (!command || !ft_strncmp(command, "key", 3))
		{
			printf("\n");
			return (0);
		}
		if (command && *command)
			add_history(command);
		else
			continue ;
		validate_input(command);
		arr = wrapper_ft_split_with_quotes(command);
		free(command);
		minishell(arr, &ms.env);
		free(prompt);
	}
	rl_clear_history();
	ft_free_2d_array(ms.env);
	return (0);
}

// int	main(void)
// {
// 	char		*command;
// 	extern char	**environ;
// 	char		**arr;
// 	char		**env;

// 	env = cpy_env(environ);
// 	command = ft_strdup("echo $PWD/*");
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
