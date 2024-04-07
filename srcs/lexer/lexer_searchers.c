/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_searchers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnikifor <dnikifor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/07 05:05:56 by dnikifor          #+#    #+#             */
/*   Updated: 2024/04/07 22:31:58 by dnikifor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

/**
 * @brief	Function that checks for brackets which are out of the quotes
 * @param	str command line string
 * @return	@c `> 0` if exist, @c `0` otherwise
 */
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
		check_if_inside_quotes(str, &i, &quote_type);
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

/**
 * @brief	Function that checks for redirects which are out of the quotes
 * @param	str command line string
 * @return	@c `> 0` if exist, @c `0` otherwise
 */
int	redir_search(char *str)
{
	int	i;
	int	quote_type;
	int	key;

	i = 0;
	quote_type = 0;
	key = 0;
	while (str[i] != NULL_TERM)
	{
		check_if_inside_quotes(str, &i, &quote_type);
		if (!quote_type)
		{
			if (str[i] == REDIR_L || str[i] == REDIR_R)
				key++;
			i++;
		}
		else
			i++;
	}
	return (key > 0);
}
