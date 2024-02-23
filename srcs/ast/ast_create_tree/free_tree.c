/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_tree.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dshatilo <dshatilo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 18:01:13 by dshatilo          #+#    #+#             */
/*   Updated: 2024/02/23 16:01:21 by dshatilo         ###   ########.fr       */
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
	int	type;

	if (*root == NULL)
		return ;
	type = (*root)->type;
	if (type == T_BRACKET)
	{
		if ((*root)->left)
			free_tree(&((*root)->left));
	}
	else if (type == T_AND || type == T_OR || type == T_PIPE
		|| type == T_COMMAND || type == T_COMMAND_BR)
	{
		if ((*root)->left)
			free_tree(&((*root)->left));
		if ((*root)->right)
			free_tree(&((*root)->right));
	}
	free(*root);
	*root = NULL;
}
