/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_tree.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dshatilo <dshatilo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 18:01:13 by dshatilo          #+#    #+#             */
/*   Updated: 2024/02/21 14:13:13 by dshatilo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

void	free_tree(t_node **root)
{
	int	type;

	if (*root == NULL)
		return ;
	type = (*root)->type;
	if (type == T_CMD_SIMPLE)
		free(((t_cmd_simple *)(*root))->cmd);
	else if (type == T_REDIR)
		free(((t_redir *)(*root))->str);
	else if (type == T_BRACKET)
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
