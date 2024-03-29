/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   constructors_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dshatilo <dshatilo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 13:21:27 by dshatilo          #+#    #+#             */
/*   Updated: 2024/03/29 16:07:16 by dshatilo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../headers/minishell.h"

t_command_br	*init_t_command_br(void)
{
	t_command_br	*node;

	node = (t_command_br *)ft_calloc(1, sizeof(t_command_br));
	if (!node)
		return (0);
	node->type = T_COMMAND_BR;
	return (node);
}

t_redir	*init_t_redir(void)
{
	t_redir	*node;

	node = (t_redir *)ft_calloc(1, sizeof(t_redir));
	if (!node)
		return (0);
	node->type = T_REDIR;
	return (node);
}
