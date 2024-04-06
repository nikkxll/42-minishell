/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   apply_append.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dshatilo <dshatilo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 11:42:17 by dshatilo          #+#    #+#             */
/*   Updated: 2024/04/06 13:39:48 by dshatilo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../headers/minishell.h"

int	apply_append(char *redir, t_minishell *ms, int *out)
{
	int		status;
	int		fd;

	close(*out);
	while (*redir == SPACE)
		redir++;
	status = check_redir(&redir, ms);
	if (status != 0)
		return (status);
	fd = open(redir, O_CREAT | O_WRONLY | O_APPEND, 0644);
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
