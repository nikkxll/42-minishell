/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   apply_heredoc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dshatilo <dshatilo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 12:21:32 by dshatilo          #+#    #+#             */
/*   Updated: 2024/04/17 20:11:59 by dshatilo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

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
