/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   traverse_tree.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnikifor <dnikifor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 13:17:46 by dshatilo          #+#    #+#             */
/*   Updated: 2024/04/10 19:53:07 by dnikifor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

/**
 * @brief	Traverse the AST tree
 * @note	This function recursively traverses the AST tree rooted at the given
 * node. Depending on the type of the node, it calls the corresponding traversal
 * function to execute the appropriate action. After traversing the subtree,
 * it frees the memory allocated for the tree nodes.
 * @param	root Pointer to the root of the shell command tree
 * @param	ms Pointer to the minishell structure
 * @return	Returns the status of the traversal process
 */
int	traverse_tree(t_node **root, t_minishell *ms)
{
	int		type;
	int		status;

	status = true;
	type = (*root)->type;
	if (type == T_AND)
		status = traverse_and(root, ms);
	else if (type == T_OR)
		status = traverse_or(root, ms);
	else if (type == T_PIPE)
		status = traverse_pipe(root, ms);
	else if (type == T_BRACKET)
		status = traverse_bracket(root, ms);
	else if (type == T_COMMAND_BR)
		status = traverse_command_br(root, ms);
	else if (type == T_COMMAND)
		status = traverse_command(((t_command *)*root)->cmd,
				((t_redir *)((t_command *)*root)->redir)->str, ms);
	free_tree(root);
	return (status);
}

/**
 * @brief	Traverse the AND logical operator node
 * @note	This function traverses the tree rooted at the given AND logical
 * operator node. It first traverses the left part. If the traversal of
 * the left part succeeds (i.e., returns a status of 0), it then traverses
 * the right part. The status of the traversal process is determined by the
 * status of the right traversal.
 * @param	root Pointer to the root of the AND logical operator node
 * @param	ms Pointer to the minishell structure
 * @return	Returns the status of the traversal process
 */
int	traverse_and(t_node **root, t_minishell *ms)
{
	int		status;
	t_node	*node;

	node = *root;
	status = traverse_tree(&(node->left), ms);
	if (status == 0)
		status = traverse_tree(&(node->right), ms);
	return (status);
}

/**
 * @brief	Traverse the OR logical operator node
 * @note	This function traverses the tree rooted at the given OR logical
 * operator node. It first traverses the left part. If the traversal of the
 * left subtree fails (i.e., returns a status other than 0), it then traverses
 * the right part. The status of the traversal process is determined by the
 * status of the right traversal.
 * @param	root Pointer to the root of the OR logical operator node
 * @param	ms Pointer to the minishell structure
 * @return	Returns the status of the traversal process
 */
int	traverse_or(t_node **root, t_minishell *ms)
{
	int		status;
	t_node	*node;

	node = *root;
	status = traverse_tree(&(node->left), ms);
	if (status != 0)
		status = traverse_tree(&(node->right), ms);
	return (status);
}
