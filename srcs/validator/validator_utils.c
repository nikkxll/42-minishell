/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validator_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnikifor <dnikifor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 16:43:09 by dnikifor          #+#    #+#             */
/*   Updated: 2024/02/19 17:52:50 by dnikifor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

void	check_if_inside_quotes_with_decr(char *str, int *i, int *quote_type)
{
	if (str[*i] == S_QUOTE && *quote_type == S_QUOTE)
	{
		*quote_type = 0;
		(*i)--;
	}
	else if (str[*i] == S_QUOTE && *quote_type == 0)
	{
		*quote_type = S_QUOTE;
		(*i)--;
	}
	else if (str[*i] == D_QUOTE && *quote_type == D_QUOTE)
	{
		*quote_type = 0;
		(*i)--;
	}
	else if (str[*i] == D_QUOTE && *quote_type == 0)
	{
		*quote_type = D_QUOTE;
		(*i)--;
	}
}

void	check_if_inside_quotes_with_incr(char *str, int *i, int *quote_type)
{
	if (str[*i] == S_QUOTE && *quote_type == S_QUOTE)
	{
		*quote_type = 0;
		(*i)++;
	}
	else if (str[*i] == S_QUOTE && *quote_type == 0)
	{
		*quote_type = S_QUOTE;
		(*i)++;
	}
	else if (str[*i] == D_QUOTE && *quote_type == D_QUOTE)
	{
		*quote_type = 0;
		(*i)++;
	}
	else if (str[*i] == D_QUOTE && *quote_type == 0)
	{
		*quote_type = D_QUOTE;
		(*i)++;
	}
}

int	check_if_backslash_or_semicolon_exist(char *str, int quote_type)
{
	int	i;

	i = 0;
	while (str[i] != NULL_TERM)
	{
		check_if_inside_quotes_with_incr(str, &i, &quote_type);
		if (!quote_type)
		{
			if (str[i] == SEMICOLON || str[i] == BACKSLASH)
				return (INVALID);
			i++;
		}
		else
			i++;
	}
	return (VALID);
}
