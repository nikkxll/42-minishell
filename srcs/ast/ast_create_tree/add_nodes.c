/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_nodes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dshatilo <dshatilo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 14:44:20 by dshatilo          #+#    #+#             */
/*   Updated: 2024/02/23 16:19:04 by dshatilo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../headers/minishell.h"

/**
 * @brief	Functions to add nodes to a binary tree based on the type 
 * 			of the current node.
 * 
 * @param	data A pointer to the structure containing information about
 * 			the type of current node.
 * @param	root A double pointer indicating where to save the current node.
 * @return	@c `true` if successful, @c `false` if an error occurs.
 */

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

	redir = init_t_redir();
	if (redir == NULL)
		return (false);
	redir->str = data->str_left;
	(*root)->left = (t_node *)redir;
	status = create_tree(data->str_right, &((*root)->right));
	if (status == false)
		return (false);
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
