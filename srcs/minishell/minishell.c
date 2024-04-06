// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   minishell.c                                        :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: dshatilo <dshatilo@student.hive.fi>        +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2024/02/21 15:09:34 by dshatilo          #+#    #+#             */
// /*   Updated: 2024/04/07 00:55:06 by dshatilo         ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */

// #include "../../headers/minishell.h"

// int	pain(void)
// {
// 	char		*command;
// 	extern char	**environ;
// 	// char		**arr;
// 	char		*folder_name;
// 	char		*prompt;
// 	t_node		*root;
// 	t_minishell	ms;

// 	ms.env = cpy_env(environ);
// 	ms.exit_status = SUCCESS;
// 	ms.exit_status = pwd_init(&(ms.env), &(ms.pwd));
// 	if (ms.exit_status != SUCCESS)
// 		return (ms.exit_status);
// 	ms.exit_status = shlvl_init(&(ms.env));
// 	if (ms.exit_status != SUCCESS)
// 		return (ms.exit_status);
// 	ms.is_parent = true;
// 	ms.is_oldpwd_unset = false;
// 	while (1)
// 	{
// 		get_current_folder_name(&folder_name);
// 		get_prompt(folder_name, &prompt, ft_itoa(ms.exit_status));
// 		command = readline(prompt);
// 		if (is_blank_string(command))
// 			continue ;
// 		if (!command || !ft_strncmp(command, "key", 3))
// 		{
// 			printf("\n");
// 			return (0);
// 		}
// 		if (command && *command)
// 			add_history(command);
// 		else
// 			continue ;
// 		validate_input(command);
// 		root = NULL;
// 		create_tree(command, &root);
// 		traverse_tree(&root, &ms);
// 		// arr = wrapper_ft_split_with_quotes(command);
// 		free(command);
// 		// minishell(arr, &ms);
// 		free(prompt);
// 	}
// 	rl_clear_history();
// 	ft_free_2d_array(ms.env);
// 	return (0);
// }

// // // int	main(void)
// // // {
// // // 	char		*command;
// // // 	extern char	**environ;
// // // 	// char		**arr;
// // // 	t_minishell	ms;
// // // 	t_node		*root;

// // // 	ms.env = cpy_env(environ);
// // // 	command = ft_strdup("echo hi  >> file");
// // // 	// while (1)
// // // 	// {
// // // 	// 	command = readline("e-bash > ");
// // // 	// 	if (!command)
// // // 	// 	{
// // // 	// 		printf("\n");
// // // 	// 		break ;
// // // 	// 	}
// // // 	// 	if (command && *command)
// // // 	// 		add_history(command);
// // // 		ms.exit_status = validate_input(command);
// // // 		root = NULL;
// // // 		ms.exit_status = create_tree(command, &root);
// // // 		ms.exit_status = traverse_tree(&root, &ms);
// // // 		// arr = wrapper_ft_split_with_quotes(command);
// // // 		// minishell(arr, &ms);
// // // 	// }
// // // 	// rl_clear_history();
// // // 	ft_free_2d_array(ms.env);
// // // 	free(command);
// // // 	return (0);
// // // }