/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_splitter.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnikifor <dnikifor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 14:39:12 by dnikifor          #+#    #+#             */
/*   Updated: 2024/02/20 19:24:23 by dnikifor         ###   ########.fr       */
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

int	brackets_search(char *str)
{
	int	i;
	int	quote_type;
	int	key;

	i = 0;
	quote_type = 0;
	key = 0;
	while (str[i] != NULL_TERM)
	{
		check_if_inside_quotes_with_incr(str, &i, &quote_type);
		if (!quote_type)
		{
			if (str[i] == O_ROUND)
				key++;
			i++;
		}
		else
			i++;
	}
	return (key > 0);
}

int	compound_block(t_node_data **node, char *str, int type, int i)
{
	if (brackets_search(str))
		return (set_node_data_compound_with_brackets(node, str,
				(int)ft_strlen(str), T_COMMAND));
	return (0);
}

int	ft_error(char *message, int code)
{
	ft_putendl_fd(message, 2);
	return (code);
}

int	parenthesis_quotes_checker(t_node_data **node, char *str, int type,
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
			status = brackets_block(node, str, type, i);
		else if (type == T_COMMAND_BR)
			status = compound_block(node, str, type, i);
		else if (type == T_SIMPLE)
			status = set_node_data(node, str, (int)ft_strlen(str), T_SIMPLE);
		if (status > 0)
			return (status);
		else if (status < 0)
			return (ft_error("Error\n", -1));
		i--;
	}
	return (parenthesis_quotes_checker(node, str, type + 1,
			(int)ft_strlen(str) - 1));
}

int	main()
{
	t_node_data	*node;
	int			status;

	char str[1000] = "(cmd && cmd) > out";
	status = parenthesis_quotes_checker(&node, str, T_AND,
			(int)ft_strlen(str) - 1);
	printf("%d\n", node->type);
	printf("%s\n", node->str_left);
	printf("%s\n", node->str_right);
	return (0);
}
