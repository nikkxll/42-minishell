/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   apply_heredoc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnikifor <dnikifor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 12:21:32 by dshatilo          #+#    #+#             */
/*   Updated: 2024/04/18 23:54:02 by dnikifor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

/**
 * @brief	Apply a here document redirection
 * @note	This function opens the file specified by the here document filename
 * for reading and associates it with the input file descriptor. It closes the
 * previous input file descriptor if it was open. If successful, it returns
 * @c `0`. If there is an error opening the file or unlinking it after opening,
 * it returns a non-zero status.
 * @param	heredoc The filename of the here document
 * @param	in      Pointer to the input file descriptor
 * @return	@c `0` if successful, non-zero otherwise
 */
int	apply_heredoc(char *heredoc, int *in)
{
	int		status;
	int		fd;

	status = 0;
	if (*in != -1)
		close(*in);
	fd = open(heredoc, O_RDONLY);
	if (unlink(heredoc) == -1)
		print_err_msg(heredoc, ": Can't delete file\n");
	if (fd != -1)
		*in = fd;
	else
	{
		status = GENERIC_ERROR;
		perror_err_msg(heredoc, "");
	}
	return (status != 0);
}
