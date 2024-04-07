/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_common_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnikifor <dnikifor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 12:43:34 by dnikifor          #+#    #+#             */
/*   Updated: 2024/04/07 22:31:34 by dnikifor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

/**
 * @brief	Function that checks if number if odd
 * @param	number number to check
 * @return	@c `1` if odd, @c `0` otherwise
 */
t_bool	is_odd(int number)
{
	return (number % 2);
}

/**
 * @brief	Function that checks if we are inside the round brackets
 * @param	str string that coming from readline function
 * @param	point current index to point in @c `str`
 * @return	@c `0` if we are inside the brackets, @c `!0` otherwise
 */
int	round_brackets_check(char *str, int point)
{
	int	i;
	int	key;
	int	quote_type;

	i = (int)ft_strlen(str) - 1;
	key = 0;
	quote_type = 0;
	while (i >= point)
	{
		check_if_inside_quotes(str, &i, &quote_type);
		if (!quote_type)
		{
			if (str[i] == O_ROUND)
				key++;
			if (str[i] == C_ROUND)
				key--;
			i--;
		}
		else
			i--;
	}
	return (!key);
}

/**
 * @brief	Function that checks if we are inside the quotes
 * @param	str string that coming from readline function
 * @param	point current index to point in @c `str`
 * @param	symbol single or double quote
 * @return	@c `1` if we are outside of the quotes, @c `0` otherwise
 */
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
	return (is_odd(pair[0]) == false && is_odd(pair[1]) == false);
}

/**
 * @brief	Function that checks if the first nonspace char is opening
 * bracket
 * @param	str string that coming from readline function
 * @return	@c `1` if it is true, @c `0` otherwise
 */
int	first_nonspace_char_is_bracket(char *str)
{
	int		i;

	i = 0;
	while (str[i] != NULL_TERM)
	{
		while (str[i] == SPACE)
			i++;
		if (str[i] == O_ROUND)
			return (1);
		else
			return (0);
	}
	return (0);
}

/**
 * @brief	Function that checks if the last nonspace char is closing bracket
 * @param	str string that coming from readline function
 * @return	@c `1` if it is true, @c `0` otherwise
 */
int	last_nonspace_char_is_bracket(char *str)
{
	int		i;

	i = (int)ft_strlen(str) - 1;
	while (i >= 0)
	{
		while (str[i] == SPACE)
			i--;
		if (str[i] == C_ROUND)
			return (1);
		else
			return (0);
	}
	return (0);
}
