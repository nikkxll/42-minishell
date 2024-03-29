/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_tree.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dshatilo <dshatilo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 18:01:13 by dshatilo          #+#    #+#             */
/*   Updated: 2024/03/30 00:20:18 by dshatilo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../headers/minishell.h"

/**
 * @brief	Recursively frees the memory allocated for a binary tree.
 * 
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
		free(((t_redir *)(*root))->str);
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
