/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_nodes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dshatilo <dshatilo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 14:44:20 by dshatilo          #+#    #+#             */
/*   Updated: 2024/03/05 11:38:10 by dshatilo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../headers/minishell.h"

/**
 * @brief	Functions to add nodes to a binary tree based on the type 
 * 			of the current node.
 * 
 * @param	info A pointer to the structure containing information about
 * 			the type of current node.
 * @param	root A double pointer indicating where to save the current node.
 * @return	@c `true` if successful, @c `false` if an error occurs.
 */

t_bool	add_and_or_pipe_trees(t_node_info *info, t_node **root)
{
	t_bool	status;

	status = create_tree(info->str_left, &((*root)->left));
	if (status == true)
		status = create_tree(info->str_right, &((*root)->right));
	return (status);
}

t_bool	add_bracket(t_node_info *info, t_node **root)
{
	t_bool	status;

	status = create_tree(info->str_left, &((*root)->left));
	return (status);
}

t_bool	add_command(t_node_info *info, t_node **root)
{
	t_bool	status;
	t_redir	*redir;

	redir = init_t_redir();
	if (redir == NULL)
		return (false);
	redir->str = info->str_left;
	(*root)->left = (t_node *)redir;
	status = create_tree(info->str_right, &((*root)->right));
	if (status == false)
		return (false);
	return (true);
}

t_bool	add_command_br(t_node_info *info, t_node **root)
{
	t_bool	status;
	t_redir	*redir;

	redir = init_t_redir();
	if (redir == NULL)
		return (false);
	redir->str = ft_strdup(info->str_left);
	if (redir->str == NULL)
	{
		free(redir);
		return (false);
	}
	(*root)->left = (t_node *)redir;
	status = create_tree(info->str_right, &((*root)->right));
	if (status == false)
		return (false);
	return (true);
}

t_bool	add_cmd_simple(t_node_info *info, t_node **root)
{
	((t_cmd_simple *)(*root))->cmd = info->str_left;
	return (true);
}
