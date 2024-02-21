/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_splitter_blocks.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnikifor <dnikifor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 13:55:41 by dnikifor          #+#    #+#             */
/*   Updated: 2024/02/21 14:30:01 by dnikifor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../headers/minishell.h"

int	and_if_condition_block(t_node_data **node, char *str, int type, int i)
{
	if (str[i] == AND && str[i - 1] == AND)
	{
		if (round_brackets_check(str, i)
			&& quote_check(str, i, S_QUOTE)
			&& quote_check(str, i, D_QUOTE))
			return (set_node_data(node, str, i, T_AND));
		else
			return (parenthesis_quotes_checker(node, str, type, i - 2));
	}
	else if (str[i] == PIPE && str[i - 1] == PIPE)
	{
		if (round_brackets_check(str, i)
			&& quote_check(str, i, S_QUOTE)
			&& quote_check(str, i, D_QUOTE))
			return (set_node_data(node, str, i, T_OR));
		else
			return (parenthesis_quotes_checker(node, str, type, i - 2));
	}
	return (0);
}

int	pipe_block(t_node_data **node, char *str, int type, int i)
{
	if (str[i] == PIPE)
	{
		if (round_brackets_check(str, i)
			&& quote_check(str, i, S_QUOTE)
			&& quote_check(str, i, D_QUOTE))
			return (set_node_data(node, str, i, T_PIPE));
		else
			return (parenthesis_quotes_checker(node, str, type, i - 1));
	}
	return (0);
}

int	brackets_block(t_node_data **node, char *str, int type, int i)
{
	if (first_nonspace_char_is_quote(str)
		&& last_nonspace_char_is_quote(str))
		return (set_node_data(node, str, (int)ft_strlen(str), T_BRACKET));
	return (0);
}
