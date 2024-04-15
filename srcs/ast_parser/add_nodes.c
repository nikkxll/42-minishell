/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_nodes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dshatilo <dshatilo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 14:44:20 by dshatilo          #+#    #+#             */
/*   Updated: 2024/04/15 10:58:15 by dshatilo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

/**
 * @brief	Functions to add nodes to a binary tree based on the type 
 * 			of the current node.
 * 
 * @param	info A pointer to the structure containing information about
 * 			the type of current node.
 * @param	root A double pointer indicating where to save the current node.
 * @return	@c `true` if successful, @c `false` if an error occurs.
 */

int	add_and_or_pipe_trees(t_node_info *info, t_node **root)
{
	int	status;

	status = create_tree(info->str_left, &((*root)->left));
	if (status == 0)
		status = create_tree(info->str_right, &((*root)->right));
	return (status);
}

int	add_bracket(t_node_info *info, t_node **root)
{
	int	status;

	status = create_tree(info->str_left, &((*root)->left));
	return (status);
}

int	add_command(t_node_info *info, t_node **root)
{
	t_redir	*redir;

	redir = init_t_redir();
	if (redir == NULL)
		return (MALLOC_ERR);
	redir->str = info->str_left;
	((t_command *)(*root))->redir = (t_node *)redir;
	((t_command *)(*root))->cmd = info->str_right;
	return (0);
}

int	add_command_br(t_node_info *info, t_node **root)
{
	int		status;
	t_redir	*redir;

	redir = init_t_redir();
	if (redir == NULL)
		return (MALLOC_ERR);
	redir->str = ft_strdup(info->str_left);
	if (redir->str == NULL)
	{
		free(redir);
		return (MALLOC_ERR);
	}
	(*root)->left = (t_node *)redir;
	status = create_tree(info->str_right, &((*root)->right));
	return (status);
}
