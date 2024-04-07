/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   traverse_tree.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnikifor <dnikifor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 13:17:46 by dshatilo          #+#    #+#             */
/*   Updated: 2024/04/07 23:26:02 by dnikifor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

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
