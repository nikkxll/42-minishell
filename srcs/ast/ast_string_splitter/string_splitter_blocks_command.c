/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_splitter_blocks_command.c                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnikifor <dnikifor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 13:55:41 by dnikifor          #+#    #+#             */
/*   Updated: 2024/02/21 14:30:43 by dnikifor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../headers/minishell.h"

/**
* @brief	Function which contains a T_COMMAND_BR block of string_splitter()
* recursion
* @param	node new node to embed into the Abstract Syntax Tree (AST)
* structure
* @param	str string that coming from readline function
* @param	type current meta character type
* @return	`-1` if malloc error occurs, `1` if success, `0` if condition not
* met
*/
int	command_block(t_node_info **node, char *str, int type)
{
	if (brackets_search(str))
		return (set_node_info_command_br(node, str, type));
	return (0);
}

/**
* @brief	Function which contains a T_COMMAND block of string_splitter()
* recursion
* @param	node new node to embed into the Abstract Syntax Tree (AST)
* structure
* @param	str string that coming from readline function
* @param	type current meta character type
* @return	`-1` if malloc error occurs, `1` if success, `0` if condition not
* met
*/
int	command_without_bracket_block(t_node_info **node, char *str, int type)
{
	if (redir_search(str))
		return (set_node_info_command(node, str, type));
	return (0);
}
