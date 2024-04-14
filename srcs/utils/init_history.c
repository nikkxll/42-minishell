/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_history.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnikifor <dnikifor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 11:02:33 by dshatilo          #+#    #+#             */
/*   Updated: 2024/04/13 00:05:11 by dnikifor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

void	read_history_file(t_minishell **ms);

/**
 * @brief	Initialize the minishell history
 * @note	This function initializes the minishell history by setting the
 * path to the history file. If the history file exists, it reads the history
 * from the file.
 * @param	minishell Pointer to the minishell structure
 * @return	@c `void`
 */
void	init_history(t_minishell **minishell)
{
	t_minishell	*ms;

	ms = *minishell;
	ms->history_path = ft_strjoin(ms->pwd, "/.e-bash_history");
	if (!ms->history_path)
	{
		print_err_msg("History file unsupported for current session", NULL);
		return ;
	}
	if (access(ms->history_path, F_OK) == 0)
		read_history_file(minishell);
}

/**
 * @brief	Read the minishell history from a file
 *
 * @note	This function reads the minishell history from the history file.
 * It opens the history file for reading, reads each line from the file using
 * the @c `get_next_line()` function, and adds each line to the minishell history.
 * If an error occurs while reading the file or using @c `get_next_line()`,
 * appropriate error messages are printed.
 *
 * @param	ms Pointer to the minishell structure
 * @return	@c `void`
 */
void	read_history_file(t_minishell **ms)
{
	int			fd;
	int			status;
	char		*buffer;
	char		*curr;

	fd = open((*ms)->history_path, O_RDONLY);
	if (fd == -1)
	{
		perror_err_msg("History initialization error: ", (*ms)->history_path);
		return ;
	}
	buffer = NULL;
	curr = "";
	while (curr != NULL)
	{
		curr = get_next_line(fd, &status, &buffer);
		if (curr != NULL)
			add_e_bash_history(curr, ms, 0);
	}
	if (status != 0 && buffer != NULL)
		free(buffer);
	if (status != 0)
		ft_putstr_fd("\033[0;31me-bash:\033[0;0m GNL error occured while"
			" reading history file", STDERR_FILENO);
	close(fd);
}
