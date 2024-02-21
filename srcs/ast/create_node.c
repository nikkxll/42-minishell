/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_node.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dshatilo <dshatilo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 18:54:02 by dshatilo          #+#    #+#             */
/*   Updated: 2024/02/21 10:38:44 by dshatilo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

t_bool	create_node(t_node_data *data, t_node **root)
{
	t_node	*node;

	node == NULL;
	if (data->type == T_AND)
		node = (t_node *)init_t_and();
	else if (data->type == T_OR)
		node = (t_node *)init_t_or();
	else if (data->type == T_PIPE)
		node = (t_node *)init_t_pipe();
	else if (data->type == T_BRACKET)
		node = (t_node *)init_t_bracket();
	else if (data->type == T_COMMAND)
		node = (t_node *)init_t_command();
	else if (data->type == T_COMMAND_BR)
		node = (t_node *)init_t_command_br();
	else if (data->type == T_CMD_SIMPLE)
		node = (t_node *)init_t_cmd_simple();
	if (node == NULL)
	{
		free_node_data(data);
		return (false);
	}
	*root = node;
	return (true);
}
