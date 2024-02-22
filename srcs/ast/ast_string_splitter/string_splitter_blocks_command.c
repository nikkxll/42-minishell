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

/*
* Function which contains a T_COMMAND_BR block of string_splitter() recursion
*
* Input:
* - `node` - new node to embed into the Abstract Syntax Tree (AST) structure
* - `str` - string that coming from readline function
* - `type` - current meta character type
* 
* Output:
* - `-1` if malloc error occurs, `1` if success, `0` if condition not met
*/
int	command_block(t_node_data **node, char *str, int type)
{
	if (brackets_search(str))
		return (set_node_data_command_br(node, str, type));
	return (0);
}

/*
* Function which contains a T_COMMAND block of string_splitter() recursion
*
* Input:
* - `node` - new node to embed into the Abstract Syntax Tree (AST) structure
* - `str` - string that coming from readline function
* - `type` - current meta character type
* 
* Output:
* - `-1` if malloc error occurs, `1` if success, `0` if condition not met
*/
int	command_without_bracket_block(t_node_data **node, char *str, int type)
{
	if (redir_search(str))
		return (set_node_data_command(node, str, type));
	return (0);
}
