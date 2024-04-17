/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_minishell.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dshatilo <dshatilo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 14:12:15 by dshatilo          #+#    #+#             */
/*   Updated: 2024/04/17 20:17:26 by dshatilo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

int		get_cmdline(char **cmdline, t_minishell **ms);
void	ft_readline(char **cmdline, char *prompt);
void	check_signal(t_minishell **ms);

/**
 * @brief	Runs the minishell main loop
 * @note	This function runs the main loop of the minishell, continuously
 * prompting the user for commands and executing them until termination.
 * It retrieves a command line input from the user, creates a parse tree for
 * the command line, and then traverses and executes the commands represented
 * by the parse tree. If any errors occur during command retrieval, parse tree
 * creation, or tree traversal, it updates the minishell's exit status
 * accordingly. The loop continues until termination is initiated by
 * an external event or command.
 * @param	ms Pointer to the minishell structure (`t_minishell`).
 *	Contains the environment and other necessary data for execution.
 */
void	run_minishell(t_minishell **ms)
{
	int		status;
	char	*cmdline;
	int		hd_num;

	while (true)
	{
		status = get_cmdline(&cmdline, ms);
		if (status != 0 && status != EOF)
			(*ms)->exit_status = status;
		if (status == EOF || status == MALLOC_ERR)
			break ;
		if (status == 0)
		{
			hd_num = 0;
			(*ms)->root = NULL;
			status = create_tree(cmdline, &((*ms)->root), &hd_num);
			if (status != 0)
				(*ms)->exit_status = status;
			if (status == 0)
				(*ms)->exit_status = traverse_tree(&((*ms)->root), *ms);
			free(cmdline);
		}
	}
}

/**
 * @brief	Getting command line input from the user
 * @note	This function prompts the user for a command line input by generating
 * a prompt based on the current minishell status. It then reads the input
 * using the readline library function. If successful, the function adds
 * the input to the command history and validates its syntax. If the input
 * is empty, the function recursively calls itself to get a new command line.
 * If any errors occur during prompt generation, input reading, or syntax
 * validation, appropriate error handling is performed, and the function
 * returns a status code indicating the failure.
 * @param	cmdline Pointer to a pointer to store the command line input
 * @param	ms Pointer to the minishell structure (`t_minishell`)
 * @return	Integer status code indicating the success or failure of the
 * operation
 */
int	get_cmdline(char **cmdline, t_minishell **ms)
{
	int		status;
	char	*prompt;

	status = get_prompt(&prompt, (*ms)->exit_status);
	if (status != 0)
		return (status);
	ft_readline(cmdline, prompt);
	if (*cmdline == NULL)
	{
		if (handle_ctrl_d(prompt) == MALLOC_ERR)
			ctrl_d_error_handler("Ctrl+d error occured.\n");
		return (EOF);
	}
	free(prompt);
	if (ft_strlen(*cmdline) == 0)
	{
		free(*cmdline);
		check_signal(ms);
		return (get_cmdline(cmdline, ms));
	}
	add_e_bash_history(*cmdline, ms, 1);
	status = validate_input(*cmdline);
	if (status != 0)
		free(*cmdline);
	return (status);
}

/**
 * @brief	Check if a SIGINT signal was received and update the exit status
 * accordingly
 * @note	This function checks if the global variable g_sgnl holds the
 * value @c `SIGINT`, indicating that a @c `SIGINT` signal was received. If
 * so, it updates the exit status of the minishell pointed to by @c `ms` to
 * @c `1` and resets the value of g_sgnl to @c `0`
 * @param	ms A pointer to the minishell structure
 * @return	@c `void`
 */
void	check_signal(t_minishell **ms)
{
	if (g_sgnl == SIGINT)
	{
		(*ms)->exit_status = 1;
		g_sgnl = 0;
	}
}

void	ft_readline(char **cmdline, char *prompt)
{
	signal_interceptor(INTERACTIVE);
	toggler(IMPLICIT);
	*cmdline = readline(prompt);
	signal_interceptor(IGNORE);
}
