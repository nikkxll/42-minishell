/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_history_to_file.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnikifor <dnikifor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 12:16:21 by dshatilo          #+#    #+#             */
/*   Updated: 2024/04/13 00:11:40 by dnikifor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

void	write_lst(void *str);

/**
 * @brief	Save the minishell history to a file
 * @note	This function saves the minishell history to the history file. It
 * first checks if the history file path is set. If the history file doesn't
 * exist, it prints a message indicating the creation of the history file. It
 * then opens the history file for writing, truncating it if it already exists.
 * It redirects the standard output to the history file descriptor and iterates
 * over the history list, writing each command to the file. If an error occurs
 * during file opening or redirection, appropriate error messages are printed.
 * @param	ms Pointer to the minishell structure
 * @return	@c `void`
 */
void	save_history_to_file(t_minishell *ms)
{
	int	fd;

	if (ms->history_path == NULL)
		return ;
	if (access(ms->history_path, F_OK) != 0)
		ft_printf("Creating history file :%s\n", ms->history_path);
	fd = open(ms->history_path, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd == -1 || dup2(fd, STDOUT_FILENO) == -1)
	{
		close(fd);
		perror_err_msg("Can't write to history file: ", ms->history_path);
		return ;
	}
	close(fd);
	ft_lstiter(ms->history, write_lst);
}

/**
 * @brief	Write a string to the standard output
 * @note	This function prints a string to the standard output followed by a newline character.
 * It is used as a callback function to write each command from the minishell history
 * list to the history file.
 * @param	str Pointer to the string to be written
 * @return	@c `void`
 */
void	write_lst(void *str)
{
	ft_printf("%s\n", str);
}
