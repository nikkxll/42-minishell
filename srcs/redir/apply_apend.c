/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   apply_apend.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dshatilo <dshatilo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 11:42:17 by dshatilo          #+#    #+#             */
/*   Updated: 2024/04/05 11:43:53 by dshatilo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

int	apply_apend(char *redir, t_minishell *ms, int *out)
{
	int		status;
	int		fd;

	close(*out);
	status = check_redir(&redir, ms);
	if (status != 0)
		return (status);
	fd = open(redir, O_CREAT | O_WRONLY | O_APPEND, 0644);
	if (fd != -1)
		*out = fd;
	else
	{
		status = GENERIC_ERROR;
		perror("\033[0;31me-bash\033[0;0m"); //edit error message!
	}
	free(redir);
	return (status);
}
