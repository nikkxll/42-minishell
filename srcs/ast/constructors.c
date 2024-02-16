/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   constructors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dshatilo <dshatilo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 12:12:01 by dshatilo          #+#    #+#             */
/*   Updated: 2024/02/16 13:39:07 by dshatilo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

t_and	*init_t_and(void)
{
	t_and	*node;

	node = (t_and *)ft_calloc(1, sizeof(t_and));
	if (!node)
		return (0);
	node->type = T_AND;
	return (node);
}

t_or	*init_t_or(void)
{
	t_or	*node;

	node = (t_or *)ft_calloc(1, sizeof(t_or));
	if (!node)
		return (0);
	node->type = T_OR;
	return (node);
}

t_pipe	*init_t_pipe(void)
{
	t_pipe	*node;

	node = (t_pipe *)ft_calloc(1, sizeof(t_pipe));
	if (!node)
		return (0);
	node->type = T_PIPE;
	return (node);
}

t_cmd	*init_t_cmd(void)
{
	t_cmd	*node;

	node = (t_cmd *)ft_calloc(1, sizeof(t_cmd));
	if (!node)
		return (0);
	node->type = T_CMD;
	return (node);
}
