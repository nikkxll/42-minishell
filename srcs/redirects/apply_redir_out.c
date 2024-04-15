/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   apply_redir_out.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dshatilo <dshatilo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 11:31:49 by dshatilo          #+#    #+#             */
/*   Updated: 2024/04/15 11:00:38 by dshatilo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

/**
 * @brief	Applies the output redirection operation.
 *
 * @note	This function applies the output redirection operation to the output
 * stream specified by the file descriptor pointed to by @c `out`. It closes
 * the current output stream, checks the validity of the redirection target
 * specified by @c `redir`, and opens the target file for writing. If the file
 * opening operation is successful, the output stream is redirected to the
 * opened file and the file descriptor @c `out` is updated accordingly. If
 * the operation fails, an appropriate error message is printed, and the
 * function returns a status code indicating the failure.
 * @param	redir Pointer to the redirection target string
 * @param	ms Pointer to the minishell structure @c `t_minishell`
 * @param	out Pointer to the file descriptor of the current output stream
 * @return	Integer status code indicating the success or failure of the
 * operation
 */
int	apply_redir_out(char *redir, t_minishell *ms, int *out)
{
	int		status;
	int		fd;

	close(*out);
	while (ft_isspace(*redir))
		redir++;
	status = check_redir(&redir, ms);
	if (status != 0)
		return (status);
	fd = open(redir, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd != -1)
		*out = fd;
	else
	{
		status = GENERIC_ERROR;
		perror_err_msg(redir, "");
	}
	free(redir);
	return (status);
}
