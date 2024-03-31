/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_splitter_blocks.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnikifor <dnikifor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 13:55:41 by dnikifor          #+#    #+#             */
/*   Updated: 2024/04/01 01:40:12 by dnikifor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../headers/minishell.h"

/**
 * @brief	Function which contains @c `T_AND` or @c `T_OR` block of
 * @c `string_splitter()` recursion
 * @param	node new node to embed into the Abstract Syntax Tree (AST)
 * structure
 * @param	str string that coming from readline function
 * @param	type current meta character type
 * @param	i index
 * @return	@c `-1` if malloc error occurs, @c `1` if success, @c `0`
 * if condition not met
 */
int	and_if_condition_block(t_node_info **node, char *str, int type, int i)
{
	if (str[i] == AND && str[i - 1] == AND)
	{
		if (round_brackets_check(str, i)
			&& quote_check(str, i, S_QUOTE)
			&& quote_check(str, i, D_QUOTE))
			return (set_node_info_and_or_pipe(node, str, i, T_AND));
		else
			return (string_splitter(node, str, type, i - 2));
	}
	else if (str[i] == PIPE && str[i - 1] == PIPE)
	{
		if (round_brackets_check(str, i)
			&& quote_check(str, i, S_QUOTE)
			&& quote_check(str, i, D_QUOTE))
			return (set_node_info_and_or_pipe(node, str, i, T_OR));
		else
			return (string_splitter(node, str, type, i - 2));
	}
	return (0);
}

/**
 * @brief	Function which contains @c `T_PIPE` block of @c `string_splitter()`
 * recursion
 * @param	node new node to embed into the Abstract Syntax Tree (AST)
 * structure
 * @param	str string that coming from readline function
 * @param	type current meta character type
 * @param	i index
 * @return	@c `-1` if malloc error occurs, @c `1` if success, @c `0`
 * if condition not met
 */
int	pipe_block(t_node_info **node, char *str, int type, int i)
{
	if (str[i] == PIPE)
	{
		if (round_brackets_check(str, i)
			&& quote_check(str, i, S_QUOTE)
			&& quote_check(str, i, D_QUOTE))
			return (set_node_info_and_or_pipe(node, str, i, type));
		else
			return (string_splitter(node, str, type, i - 1));
	}
	return (0);
}

/**
 * @brief	Function which contains @c `T_BRACKET` block of
 * @c `string_splitter()` recursion
 * @param	node new node to embed into the Abstract Syntax Tree (AST)
 * structure
 * @param	str string that coming from readline function
 * @param	type current meta character type
 * @return	@c `-1` if malloc error occurs, @c `1` if success, @c `0`
 * if condition not met
 */
int	brackets_block(t_node_info **node, char *str, int type)
{
	if (first_nonspace_char_is_bracket(str)
		&& last_nonspace_char_is_bracket(str))
		return (set_node_info_bracket(node, str, type));
	return (0);
}
