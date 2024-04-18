/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_tree.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnikifor <dnikifor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 18:01:13 by dshatilo          #+#    #+#             */
/*   Updated: 2024/04/18 23:37:31 by dnikifor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

/**
 * @brief	Recursively frees the memory allocated for a binary tree.
 * @param	root A double pointer to the root node of the tree
 */
void	free_tree(t_node **root)
{
	if (*root == NULL)
		return ;
	if ((*root)->type == T_BRACKET)
	{
		if ((*root)->left)
			free_tree(&((*root)->left));
	}
	else if ((*root)->type == T_REDIR)
	{
		if (((t_redir *)(*root))->redirs)
			ft_free_2d_array(((t_redir *)(*root))->redirs);
	}
	else if ((*root)->type == T_COMMAND)
	{
		free_tree(&((t_command *)(*root))->redir);
	}
	else
	{
		if ((*root)->left)
			free_tree(&((*root)->left));
		if ((*root)->right)
			free_tree(&((*root)->right));
	}
	free(*root);
	*root = NULL;
}
