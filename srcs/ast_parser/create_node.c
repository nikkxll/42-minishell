/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_node.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dshatilo <dshatilo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 18:54:02 by dshatilo          #+#    #+#             */
/*   Updated: 2024/04/15 10:58:22 by dshatilo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

/**
 * @brief	 Creates a node based on the @c `type` in the @c `info` structure.
 * 
 * @param	info A pointer to the structure containing information about
 * 			the type of current node.
 * @param	root A double pointer indicating where to save the current node.
 * @return	@c `true` if successful, @c `false` if an error occurs.
 */
t_bool	create_node(t_node_info *info, t_node **root)
{
	t_node	*node;

	node = NULL;
	if (info->type == T_AND)
		node = (t_node *)init_t_and();
	else if (info->type == T_OR)
		node = (t_node *)init_t_or();
	else if (info->type == T_PIPE)
		node = (t_node *)init_t_pipe();
	else if (info->type == T_BRACKET)
		node = (t_node *)init_t_bracket();
	else if (info->type == T_COMMAND)
		node = (t_node *)init_t_command();
	else if (info->type == T_COMMAND_BR)
		node = (t_node *)init_t_command_br();
	if (node == NULL)
	{
		free(info);
		return (false);
	}
	*root = node;
	return (true);
}
