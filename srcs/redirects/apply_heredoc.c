/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   apply_heredoc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnikifor <dnikifor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 12:21:32 by dshatilo          #+#    #+#             */
/*   Updated: 2024/04/11 15:30:11 by dnikifor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

static int	heredoc(char *limiter, int fd);

/**
 * @brief	Apply the heredoc redirection operation
 * @note	This function applies the heredoc redirection operation to the
 * input stream specified by the file descriptor pointed to by @c `in`.
 * It closes the current input stream, creates a pipe for inter-process
 * communication, and invokes the @c `heredoc` function to handle the heredoc
 * input process. If the operation is successful, the input stream is
 * redirected to the reading end of the pipe, and the file descriptor @c `in`
 * is updated accordingly. If the operation fails, an appropriate error status
 * code is returned.
 * @param	limiter Pointer to the heredoc delimiter string
 * @param	in Pointer to the file descriptor of the current input stream
 * @return	Integer status code indicating the success or failure of the
 * operation
 */
int	apply_heredoc(char *limiter, int *in)
{
	int		status;
	int		hd[2];

	close(*in);
	while (*limiter == SPACE)
		limiter++;
	if (pipe(hd) == -1)
		return (PIPE_FAILURE);
	status = heredoc(limiter, hd[WRITE]);
	close(hd[WRITE]);
	if (status != 0)
		close(hd[READ]);
	else
		*in = hd[READ];
	return (status);
}

/**
 * @brief	Handle the heredoc input process
 * @note	This function handles the heredoc input process, where the user is
 * prompted to input lines of text until a delimiter line matching the specified
 * limiter string is encountered. It continuously reads input lines from the user
 * using the readline function and writes them to the specified file descriptor
 * @c `fd`. If the limiter line is encountered, indicating the end of the heredoc
 * input, the function terminates and returns @c `0`. If any errors occur during
 * the input process, such as failure to read input or write to the file
 * descriptor, appropriate error handling is performed, and the function returns
 * an error status code.
 * @param	limiter Pointer to the heredoc delimiter string
 * @param	fd File descriptor for writing the heredoc input
 * @return	Integer status code indicating the success or failure of the
 * operation
 */
static int	heredoc(char *limiter, int fd)
{
	char	*line;
	int		isequal;

	while (true)
	{
		line = readline("> ");
		if (!line)
		{
			ft_printf("\033[1A");
			ft_printf("\033[2C");
			return (0);
		}
		isequal = ft_strcmp(limiter, line);
		if (isequal != 0)
			ft_putendl_fd(line, fd);
		free(line);
		if (isequal == 0)
			return (0);
	}
}
