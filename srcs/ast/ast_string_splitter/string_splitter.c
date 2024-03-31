/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_splitter.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnikifor <dnikifor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 14:39:12 by dnikifor          #+#    #+#             */
/*   Updated: 2024/04/01 01:40:26 by dnikifor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../headers/minishell.h"

/**
 * @brief	Function splits string in 2 parts according to the meta character
 * type
 * @param	node new node to embed into the Abstract Syntax Tree (AST)
 * structure
 * @param	str string that coming from readline function
 * @param	type current meta character type
 * @param	i index to iterate throw the string
 * @note		function uses recursion
 * @return	@c `-1` if malloc error occurs, @c `1` if success
 */
int	string_splitter(t_node_info **node, char *str, int type,
	int i)
{
	int	status;

	while (i >= 0)
	{
		if (type == T_AND || type == T_OR)
			status = and_if_condition_block(node, str, type, i);
		else if (type == T_PIPE)
			status = pipe_block(node, str, type, i);
		else if (type == T_BRACKET)
			status = brackets_block(node, str, type);
		else if (type == T_COMMAND_BR)
			status = command_block(node, str, type);
		else if (type == T_COMMAND)
			status = command_without_bracket_block(node, str, type);
		else if (type == T_CMD_SIMPLE)
			status = set_node_cmd_simple(node, str, T_CMD_SIMPLE);
		if (status > 0)
			return (status);
		else if (status < 0)
			return (-1);
		i--;
	}
	return (string_splitter(node, str, type + 1,
			ft_strlen(str) - 1));
}
