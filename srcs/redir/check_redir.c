/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dshatilo <dshatilo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 12:42:19 by dshatilo          #+#    #+#             */
/*   Updated: 2024/04/05 01:46:22 by dshatilo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

int	check_redir(char **redir, t_minishell *ms)
{
	int		status;
	char	**rdr;

	status = parse_cmd(*redir, &rdr, ms);
	if (status != 0)
		return (status);
	if (ft_arrlen((void **)rdr) != 1)
	{
		status = 1;
		print_err_msg(*redir, ": ambiguous redirect\n");
		ft_free_2d_array(rdr);
	}
	else
	{
		*redir = rdr[0];
		free(rdr);
	}
	return (status);
}