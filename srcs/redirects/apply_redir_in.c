/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   apply_redir_in.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnikifor <dnikifor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 23:03:41 by dshatilo          #+#    #+#             */
/*   Updated: 2024/04/07 22:59:59 by dnikifor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

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
