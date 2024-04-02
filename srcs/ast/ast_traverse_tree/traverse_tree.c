/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   traverse_tree.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dshatilo <dshatilo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 13:17:46 by dshatilo          #+#    #+#             */
/*   Updated: 2024/04/02 00:54:24 by dshatilo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../headers/minishell.h"

int	traverse_tree(t_node *node, char ***envp)
{
	int		type;
	int		status;

	status = true;
	type = node->type;
	if (type == T_AND)
		status = traverse_and(node, envp);
	else if (type == T_OR)
		status = traverse_or(node, envp);
	else if (type == T_PIPE)
		status = traverse_pipe(node, envp);
	else if (type == T_BRACKET)
		status = traverse_bracket(node, envp);
	else if (type == T_COMMAND_BR)
		status = traverse_command_br(node, envp);
	else if (type == T_COMMAND)
		status = traverse_command(((t_command *)node)->cmd,
				((t_redir *)((t_command *)node)->redir)->str, envp);
	free_tree(&node);
	return (status);
}

int	traverse_and(t_node *node, char ***envp)
{
	int	status;

	status = traverse_tree(node->left, envp);
	if (status == 0)
		status = traverse_tree(node->right, envp);
	return (status);
}

int	traverse_or(t_node *node, char ***envp)
{
	int	status;

	status = traverse_tree(node->left, envp);
	if (status != 0)
		status = traverse_tree(node->right, envp);
	return (status);
}
