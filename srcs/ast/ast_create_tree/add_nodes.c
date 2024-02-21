/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_nodes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dshatilo <dshatilo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 14:44:20 by dshatilo          #+#    #+#             */
/*   Updated: 2024/02/21 16:41:39 by dshatilo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../headers/minishell.h"

t_bool	add_and_or_pipe_trees(t_node_data *data, t_node **root)
{
	t_bool	status;

	status = create_tree(data->str_left, &((*root)->left));
	if (status == true)
		status = create_tree(data->str_right, &((*root)->right));
	return (status);
}

t_bool	add_bracket(t_node_data *data, t_node **root)
{
	t_bool	status;

	status = create_tree(data->str_left, &((*root)->left));
	return (status);
}

t_bool	add_command(t_node_data *data, t_node **root)
{
	t_bool	status;
	t_redir	*redir;

	status = create_tree(data->str_right, &((*root)->right));
	if (status == false)
		return (false);
	redir = init_t_redir();
	if (redir == NULL)
		return (false);
	redir->str = data->str_left;
	(*root)->left = (t_node *)redir;
	return (true);
}

t_bool	add_command_br(t_node_data *data, t_node **root)
{
	t_bool	status;
	t_redir	*redir;

	status = create_tree(data->str_right, &((*root)->right));
	if (status == false)
		return (false);
	redir = init_t_redir();
	if (redir == NULL)
		return (false);
	redir->str = data->str_left;
	(*root)->left = (t_node *)redir;
	return (true);
}

t_bool	add_cmd_simple(t_node_data *data, t_node **root)
{
	((t_cmd_simple *)(*root))->cmd = data->str_left;
	return (true);
}
