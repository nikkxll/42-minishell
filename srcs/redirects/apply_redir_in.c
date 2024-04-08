/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   apply_redir_in.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnikifor <dnikifor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 23:03:41 by dshatilo          #+#    #+#             */
/*   Updated: 2024/04/08 20:07:55 by dnikifor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

/**
 * @brief	Applies the input redirection operation
 * @note	This function applies the input redirection operation to the input
 * stream specified by the file descriptor pointed to by @c `in`. It closes the
 * current input stream, checks the validity of the redirection target specified
 * by @c `redir`, and opens the target file for reading. If the file opening
 * operation is successful, the input stream is redirected to the opened file
 * and the file descriptor @c `in` is updated accordingly. If the operation
 * fails, an appropriate error message is printed, and the function returns a
 * status code indicating the failure.
 * @param	redir Pointer to the redirection target string
 * @param	ms Pointer to the minishell structure @c `t_minishell`
 * @param	in Pointer to the file descriptor of the current input stream
 * @return	Integer status code indicating the success or failure of the
 * operation
 */
int	apply_redir_in(char *redir, t_minishell *ms, int *in)
{
	int		status;
	int		fd;

	close(*in);
	while (ft_isspace(*redir))
		redir++;
	status = check_redir(&redir, ms);
	if (status != 0)
		return (status);
	fd = open(redir, O_RDONLY);
	if (fd != -1)
		*in = fd;
	else
	{
		status = GENERIC_ERROR;
		perror_err_msg(redir, "");
	}
	free(redir);
	return (status);
}
