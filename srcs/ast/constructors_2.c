/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   constructors_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dshatilo <dshatilo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 13:21:27 by dshatilo          #+#    #+#             */
/*   Updated: 2024/02/16 13:24:07 by dshatilo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

t_redir_l	*init_t_redir_l(void)
{
	t_redir_l	*node;

	node = (t_redir_l *)ft_calloc(1, sizeof(t_redir_l));
	if (!node)
		return (0);
	node->type = T_REDIR_L;
	return (node);
}

t_redir_r	*init_t_redir_r(void)
{
	t_redir_r	*node;

	node = (t_redir_r *)ft_calloc(1, sizeof(t_redir_r));
	if (!node)
		return (0);
	node->type = T_REDIR_R;
	return (node);
}

t_redir_ll	*init_t_redir_ll(void)
{
	t_redir_ll	*node;

	node = (t_redir_ll *)ft_calloc(1, sizeof(t_redir_ll));
	if (!node)
		return (0);
	node->type = T_REDIR_LL;
	return (node);
}

t_redir_r	*init_t_redir_r(void)
{
	t_redir_r	*node;

	node = (t_redir_r *)ft_calloc(1, sizeof(t_redir_r));
	if (!node)
		return (0);
	node->type = T_REDIR_R;
	return (node);
}

t_redir_rr	*init_t_redir_rr(void)
{
	t_redir_rr	*node;

	node = (t_redir_rr *)ft_calloc(1, sizeof(t_redir_rr));
	if (!node)
		return (0);
	node->type = T_REDIR_RR;
	return (node);
}
