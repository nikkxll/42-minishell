/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parenthesis_quotes_checker.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dshatilo <dshatilo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 14:39:12 by dnikifor          #+#    #+#             */
/*   Updated: 2024/02/16 13:17:11 by dshatilo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

t_node_data	*set_node_data(char *str, int point, int type)
{
	t_node_data	*node;

	str[point] = '\0';
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

	i = 0;
	key = 0;
	while (i < point)
	{
		if (str[i] == '(')
			key++;
		if (str[i] == ')')
			key--;
		i++;
	}
	return (!key);
}

int	quote_check(char *str, int point, int symbol)
{
	int		i;
	int		pair[2];

	i = 0;
	pair[0] = 0;
	pair[1] = 0;
	while (i < point)
	{
		if (str[i] == symbol)
			pair[0]++;
		i++;
	}
	while (++point < (int)ft_strlen(str))
	{
		if (str[point] == symbol)
			pair[1]++;
	}
	return (if_odd(pair[0]) == false && if_odd(pair[1]) == false);
}

t_node_data	*parenthesis_quotes_checker(char *str, int type, int i)
{
	while (str[i] != '\0')
	{
		if (type == T_AND)
		{
			if (str[i] == '&' && str[i + 1] == '&')
			{
				if (round_brackets_check(str, i - 1)
					&& quote_check(str, i, '\'')
					&& quote_check(str, i, '\"'))
					return (set_node_data(str, i, T_AND));
				else
					parenthesis_quotes_checker(str, type, i + 2);
			}
		}
		else if (type == T_OR)
		{
			if (str[i] == '|' && str[i + 1] == '|')
			{
				if (round_brackets_check(str, i - 1)
					&& quote_check(str, i, '\'')
					&& quote_check(str, i, '\"'))
					return (set_node_data(str, i, T_OR));
				else
					parenthesis_quotes_checker(str, type, i + 2);
			}
		}
		else if (type == T_PIPE)
		{
			if (str[i] == '|')
			{
				if (round_brackets_check(str, i - 1)
					&& quote_check(str, i, '\'')
					&& quote_check(str, i, '\"'))
					return (set_node_data(str, i, T_PIPE));
				else
					parenthesis_quotes_checker(str, type, i + 1);
			}
		}
		else if (type == T_REDIR_L)
		{
			if (str[i] == '<' && str[i + 1] != '<')
			{
				if (round_brackets_check(str, i - 1)
					&& quote_check(str, i, '\'')
					&& quote_check(str, i, '\"'))
					return (set_node_data(str, i, T_REDIR_L));
				else
					parenthesis_quotes_checker(str, type, i + 1);
			}
		}
		else if (type == T_REDIR_R)
		{
			if (str[i] == '>' && str[i + 1] != '>')
			{
				if (round_brackets_check(str, i - 1)
					&& quote_check(str, i, '\'')
					&& quote_check(str, i, '\"'))
					return (set_node_data(str, i, T_REDIR_R));
				else
					parenthesis_quotes_checker(str, type, i + 1);
			}
		}
		else if (type == T_REDIR_LL)
		{
			if (str[i] == '>' && str[i + 1] == '>')
			{
				if (round_brackets_check(str, i - 1)
					&& quote_check(str, i, '\'')
					&& quote_check(str, i, '\"'))
					return (set_node_data(str, i, T_REDIR_LL));
				else
					parenthesis_quotes_checker(str, type, i + 2);
			}
		}
		else
		{
			if (str[i] == '<' && str[i + 1] == '<')
			{
				if (round_brackets_check(str, i - 1)
					&& quote_check(str, i, '\'')
					&& quote_check(str, i, '\"'))
					return (set_node_data(str, i, T_REDIR_RR));
				else
					parenthesis_quotes_checker(str, type, i + 2);
			}
		}
		i++;
	}
	return (parenthesis_quotes_checker(str, type + 1, 0));
}

int	meta_characters_check(char *str)
{
	int	i;
	int	meta[3];

	i = 0;
	meta[0] = 0;
	meta[1] = 0;
	meta[2] = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '|')
			meta[0]++;
		if (str[i] == '&')
			meta[1]++;
		if (str[i] == '<' || str[i] == '>')
			meta[2]++;
		i++;
	}
	return (meta[0] + meta[1] + meta[2]);
}

int	main()
{
	t_node_data	*node;
	char buffer[1000] = "cmd > file";

	if (meta_characters_check(buffer))
		node = parenthesis_quotes_checker(buffer, T_AND, 0);
	else
		node = set_node_data(buffer, (int)ft_strlen(buffer), T_CMD);
	printf("%d\n", node->type);
	printf("%s\n", node->str_left);
	printf("%s\n", node->str_right);
	return (0);
}
