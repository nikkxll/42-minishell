/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   apply_redir_in.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dshatilo <dshatilo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 23:03:41 by dshatilo          #+#    #+#             */
/*   Updated: 2024/04/03 23:26:32 by dshatilo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

int	apply_redir_in(char *redir, t_minishell *ms)
{
	int	status;

	redir = extend_redir(redir, ms);
	if (!redir)
		return (GENERIC_ERROR);

	free(redir);
	return (0);
}
