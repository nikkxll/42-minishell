/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parenthesis_quotes_checker.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnikifor <dnikifor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 14:39:12 by dnikifor          #+#    #+#             */
/*   Updated: 2024/02/17 20:33:34 by dnikifor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

t_node_data	*set_node_data(char *str, int point, int type)
{
	t_node_data	*node;

	str[point] = NULL_TERM;
	node = ft_calloc(1, sizeof(node));
	node->str_left = str;
	node->str_right = NULL;
	node->str_right = str + point + 1;
	node->type = type;
	return (node);
}

t_bool	if_odd(int number)
{
	return (number % 2);
}

int	round_brackets_check(char *str, int point)
{
	int	i;
	int	key;

	i = (int)ft_strlen(str) - 1;
	key = 0;
	while (i >= point)
	{
		if (str[i] == O_ROUND)
			key++;
		if (str[i] == C_ROUND)
			key--;
		i--;
	}
	return (!key);
}

int	quote_check(char *str, int point, int symbol)
{
	int		i;
	int		pair[2];

	i = (int)ft_strlen(str) - 1;
	pair[0] = 0;
	pair[1] = 0;
	while (i >= point)
	{
		if (str[i] == symbol)
			pair[0]++;
		i--;
	}
	while (--point > 0)
	{
		if (str[point] == symbol)
			pair[1]++;
	}
	return (if_odd(pair[0]) == false && if_odd(pair[1]) == false);
}

t_node_data	*parenthesis_quotes_checker(char *str, int type, int i)
{
	while (i > 0)
	{
		if (type == T_AND || type == T_OR)
		{
			if (str[i] == AND && str[i - 1] == AND)
			{
				if (round_brackets_check(str, i)
					&& quote_check(str, i, S_QUOTE)
					&& quote_check(str, i, D_QUOTE))
					return (set_node_data(str, i, T_AND));
				else
					return (parenthesis_quotes_checker(str, type, i - 2));
			}
			else if (str[i] == PIPE && str[i - 1] == PIPE)
			{
				if (round_brackets_check(str, i)
					&& quote_check(str, i, S_QUOTE)
					&& quote_check(str, i, D_QUOTE))
					return (set_node_data(str, i, T_OR));
				else
					return (parenthesis_quotes_checker(str, type, i - 2));
			}
		}
		else if (type == T_PIPE)
		{
			if (str[i] == PIPE)
			{
				if (round_brackets_check(str, i)
					&& quote_check(str, i, S_QUOTE)
					&& quote_check(str, i, D_QUOTE))
					return (set_node_data(str, i, T_PIPE));
				else
					return (parenthesis_quotes_checker(str, type, i - 1));
			}
		}
		else if (type == T_REDIR_L)
		{
			if (str[i] == REDIR_L && str[i - 1] != REDIR_L)
			{
				if (round_brackets_check(str, i)
					&& quote_check(str, i, S_QUOTE)
					&& quote_check(str, i, D_QUOTE))
					return (set_node_data(str, i, T_REDIR_L));
				else
					return (parenthesis_quotes_checker(str, type, i - 1));
			}
		}
		else if (type == T_REDIR_R)
		{
			if (str[i] == REDIR_R && str[i - 1] != REDIR_R)
			{
				if (round_brackets_check(str, i)
					&& quote_check(str, i, S_QUOTE)
					&& quote_check(str, i, D_QUOTE))
					return (set_node_data(str, i, T_REDIR_R));
				else
					return (parenthesis_quotes_checker(str, type, i - 1));
			}
		}
		else if (type == T_REDIR_LL)
		{
			if (str[i] == REDIR_R && str[i - 1] == REDIR_R)
			{
				if (round_brackets_check(str, i)
					&& quote_check(str, i, S_QUOTE)
					&& quote_check(str, i, D_QUOTE))
					return (set_node_data(str, i, T_REDIR_LL));
				else
					parenthesis_quotes_checker(str, type, i - 2);
			}
		}
		else
		{
			if (str[i] == REDIR_L && str[i - 1] == REDIR_L)
			{
				if (round_brackets_check(str, i)
					&& quote_check(str, i, S_QUOTE)
					&& quote_check(str, i, D_QUOTE))
					return (set_node_data(str, i, T_REDIR_RR));
				else
					return (parenthesis_quotes_checker(str, type, i - 2));
			}
		}
		i--;
	}
	return (parenthesis_quotes_checker(str, type + 1, (int)ft_strlen(str) - 1));
}

int	meta_characters_check(char *str)
{
	int	i;
	int	meta[3];

	i = 0;
	meta[0] = 0;
	meta[1] = 0;
	meta[2] = 0;
	while (str[i] != NULL_TERM)
	{
		if (str[i] == PIPE)
			meta[0]++;
		if (str[i] == AND)
			meta[1]++;
		if (str[i] == REDIR_L || str[i] == REDIR_R)
			meta[2]++;
		i++;
	}
	return (meta[0] + meta[1] + meta[2]);
}

int	main()
{
	t_node_data	*node;
	char str[1000] = "(cmd || file) < cmd << cmd (cmd || cmd)";

	if (meta_characters_check(str))
		node = parenthesis_quotes_checker(str, T_AND, (int)ft_strlen(str) - 1);
	else
		node = set_node_data(str, (int)ft_strlen(str), T_CMD);
	printf("%d\n", node->type);
	printf("%s\n", node->str_left);
	printf("%s\n", node->str_right);
	return (0);
}
