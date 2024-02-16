/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_node.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dshatilo <dshatilo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 18:54:02 by dshatilo          #+#    #+#             */
/*   Updated: 2024/02/16 13:38:52 by dshatilo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

t_bool	create_node(t_node_data *data, t_node **base)
{
	t_node	*node;
	int		type;

	type = data->type;
	if (type == T_AND)
		node = (t_node *)init_t_and();
	else if (type == T_OR)
		node = (t_node *)init_t_or();
	else if (type == T_PIPE)
		node = (t_node *)init_t_pipe();
	else if (type == T_REDIR_L)
		node = (t_node *)init_t_redir_l();
	else if (type == T_REDIR_R)
		node = (t_node *)init_t_redir_r();
	else if (type == T_REDIR_LL)
		node = (t_node *)init_t_redir_lL();
	else if (type == T_REDIR_RR)
		node = (t_node *)init_t_redir_r();
	if (node == NULL)
	{
		free_node_data(data);
		return (false);
	}
	*base = node;
	return (true);
}
