/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_e_bash_history.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnikifor <dnikifor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 11:08:31 by dshatilo          #+#    #+#             */
/*   Updated: 2024/04/13 00:05:47 by dnikifor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

void	add_to_history_list(char *cmd, char *cmdline, t_minishell **minishell);
void	print_err_history(char *cmd);

/**
 * @brief	Add a command to the minishell history
 * @note	This function adds a command to the minishell history. It removes 
 * any trailing newline characters from the command line, adds the command to
 * the readline history, and then adds the command to the minishell history list.
 * If the mode is @c `0`, indicating that the command line string was dynamically
 * allocated and needs to be freed, this function frees the memory for the
 * command line string after adding it to the history list.
 * @param	cmdline The command line string to add to the history
 * @param	minishell Pointer to the minishell structure
 * @param	mode Flag indicating whether the command line string needs to be
 * freed (@c `0` for yes, @c `1` for no)
 * @return	@c `void`
 */
void	add_e_bash_history(char *cmdline, t_minishell **minishell, int mode)
{
	t_minishell	*ms;
	char		*cmd;

	ms = *minishell;
	ft_remove_nl(cmdline);
	add_history(cmdline);
	if (ms->history_path == NULL)
		return ;
	cmd = ft_strdup(cmdline);
	if (!cmd)
	{
		print_err_history(cmdline);
		return ;
	}
	if (mode == 0)
		free(cmdline);
	add_to_history_list(cmd, cmdline, minishell);
}

/**
 * @brief	Add a command to the minishell history list
 * @note	This function adds a command to the minishell history list.
 * It creates a new list node containing the command string, adds the node
 * to the end of the history list, and then checks if the size of the history
 * list exceeds the maximum allowed size. If the size exceeds the maximum,
 * it removes the first node from the history list to maintain the
 * maximum size.
 * @param	cmd The command string copy to add to the history list
 * @param	cmdline The original command line string
 * @param	minishell Pointer to the minishell structure
 * @return	@c `void`
 */
void	add_to_history_list(char *cmd, char *cmdline, t_minishell **minishell)
{
	t_list		*curr;
	t_minishell	*ms;

	ms = *minishell;
	curr = ft_lstnew((void *)cmd);
	if (!curr)
	{
		free(cmd);
		print_err_history(cmdline);
		return ;
	}
	ft_lstadd_back(&(ms->history), curr);
	if (ft_lstsize(ms->history) > HIST_SIZE)
		ft_lstdel_front(&(ms->history), free);
}

/**
 * @brief	Print an error message for history addition
 * @note	This function prints an error message indicating that a command
 * cannot be added to the history.
 * @param	cmd The command that couldn't be added to the history
 * @return	@c `void`
 */
void	print_err_history(char *cmd)
{
	ft_putstr_fd("\033[0;31me-bash: \033[0;0m", STDERR_FILENO);
	ft_putstr_fd(cmd, STDERR_FILENO);
	ft_putstr_fd(": can't add to history, ", STDERR_FILENO);
}
