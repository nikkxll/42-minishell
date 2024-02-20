/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_splitter.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnikifor <dnikifor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 14:39:12 by dnikifor          #+#    #+#             */
/*   Updated: 2024/02/20 16:11:13 by dnikifor         ###   ########.fr       */
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

int	left_redirect_block(t_node_data **node, char *str, int type, int i)
{
	if (str[i] == REDIR_L && str[i - 1] != REDIR_L)
	{
		if (round_brackets_check(str, i)
			&& quote_check(str, i, S_QUOTE)
			&& quote_check(str, i, D_QUOTE))
			return (set_node_data(node, str, i, T_REDIR_L));
		else
			return (parenthesis_quotes_checker(node, str, type, i - 1));
	}
	return (0);
}

int	right_redirect_block(t_node_data **node, char *str, int type, int i)
{
	if (str[i] == REDIR_R && str[i - 1] != REDIR_R)
	{
		if (round_brackets_check(str, i)
			&& quote_check(str, i, S_QUOTE)
			&& quote_check(str, i, D_QUOTE))
			return (set_node_data(node, str, i, T_REDIR_R));
		else
			return (parenthesis_quotes_checker(node, str, type, i - 1));
	}
	return (0);
}

int	double_left_redirect_block(t_node_data **node, char *str, int type, int i)
{
	if (str[i] == REDIR_L && str[i - 1] == REDIR_L)
	{
		if (round_brackets_check(str, i)
			&& quote_check(str, i, S_QUOTE)
			&& quote_check(str, i, D_QUOTE))
			return (set_node_data(node, str, i, T_REDIR_LL));
		else
			return (parenthesis_quotes_checker(node, str, type, i - 2));
	}
	return (0);
}

int	double_right_redirect_block(t_node_data **node, char *str, int type, int i)
{
	if (str[i] == REDIR_R && str[i - 1] == REDIR_R)
	{
		if (round_brackets_check(str, i)
			&& quote_check(str, i, S_QUOTE)
			&& quote_check(str, i, D_QUOTE))
			return (set_node_data(node, str, i, T_REDIR_RR));
		else
			return (parenthesis_quotes_checker(node, str, type, i - 2));
	}
	return (0);
}

int	redirect_block(t_node_data **node, char *str, int type, int i)
{
	if (str[i] == REDIR_L && str[i - 1] != REDIR_L)
		return (left_redirect_block(node, str, type, i));
	else if (str[i] == REDIR_R && str[i - 1] != REDIR_R)
		return (right_redirect_block(node, str, type, i));
	else if (str[i] == REDIR_L && str[i - 1] == REDIR_L)
		return (double_left_redirect_block(node, str, type, i));
	else if (str[i] == REDIR_R && str[i - 1] == REDIR_R)
		return (double_right_redirect_block(node, str, type, i));
	return (0);
}

int	brackets_block(t_node_data **node, char *str, int type, int i)
{
	if (first_nonspace_char_is_quote(str)
		&& last_nonspace_char_is_quote(str))
		return (set_node_data(node, str, (int)ft_strlen(str), T_BRACKET));
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
		else if (type == T_REDIR_L || type == T_REDIR_R
			|| type == T_REDIR_LL || type == T_REDIR_RR)
			status = redirect_block(node, str, type, i);
		else if (type == T_BRACKET)
			status = brackets_block(node, str, type, i);
		else if (type == T_CMD)
			status = set_node_data(node, str, (int)ft_strlen(str), T_CMD);
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

	char str[1000] = "cmd || (cmd && cmd)";
	status = parenthesis_quotes_checker(&node, str, T_AND,
			(int)ft_strlen(str) - 1);
	printf("%d\n", node->type);
	printf("%s\n", node->str_left);
	printf("%s\n", node->str_right);
	return (0);
}
