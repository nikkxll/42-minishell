/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dshatilo <dshatilo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 12:42:19 by dshatilo          #+#    #+#             */
/*   Updated: 2024/04/15 11:00:36 by dshatilo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

/**
 * @brief	Check the validity of a redirection target
 * @note	This function checks the validity of a redirection target specified
 * by the `redir` string. It first parses the `redir` string to identify
 * individual redirection specifications. If parsing is successful, the function
 * updates the `redir` pointer to point to the valid redirection target.
 * Otherwise, if parsing fails or there are multiple redirection targets,
 * it prints an error message and returns a status code indicating the failure.
 * @param	redir Pointer to the redirection target string
 * @param	ms Pointer to the minishell structure (`t_minishell`)
 * @return	Integer status code indicating the success or failure of the
 * operation
 */
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
