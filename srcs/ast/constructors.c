/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   constructors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dshatilo <dshatilo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 12:12:01 by dshatilo          #+#    #+#             */
/*   Updated: 2024/02/21 13:01:43 by dshatilo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

t_and	*init_t_and(void)
{
	t_and	*node;

	node = (t_and *)ft_calloc(1, sizeof(t_and));
	if (!node)
		return (NULL);
	node->type = T_AND;
	return (node);
}

t_or	*init_t_or(void)
{
	t_or	*node;

	node = (t_or *)ft_calloc(1, sizeof(t_or));
	if (!node)
		return (NULL);
	node->type = T_OR;
	return (node);
}

t_pipe	*init_t_pipe(void)
{
	t_pipe	*node;

	node = (t_pipe *)ft_calloc(1, sizeof(t_pipe));
	if (!node)
		return (NULL);
	node->type = T_PIPE;
	return (node);
}

t_bracket	*init_t_bracket(void)
{
	t_bracket	*node;

	node = (t_bracket *)ft_calloc(1, sizeof(t_bracket));
	if (!node)
		return (NULL);
	node->type = T_BRACKET;
	return (node);
}

t_command	*init_t_command(void)
{
	t_command	*node;

	node = (t_command *)ft_calloc(1, sizeof(t_command));
	if (!node)
		return (NULL);
	node->type = T_COMMAND;
	return (node);
}
