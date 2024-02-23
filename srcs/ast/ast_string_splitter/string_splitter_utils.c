/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_splitter_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnikifor <dnikifor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 12:43:34 by dnikifor          #+#    #+#             */
/*   Updated: 2024/02/23 15:25:52 by dnikifor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../headers/minishell.h"

/**
* @brief	Function that checks if number if odd
* @param	number number to check
* @return	`1` if odd, `0` otherwise
*/
t_bool	if_odd(int number)
{
	return (number % 2);
}

/**
* @brief	Function that checks if we are inside the round brackets
* @param	str string that coming from readline function
* @param	point current index to point in `str`
* @return	`0` if we are inside the brackets, `non zero` otherwise
*/
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

/**
* @brief	Function that checks if we are inside the quotes
* @param	str string that coming from readline function
* @param	point current index to point in `str`
* @param	symbol single or double quote
* @return	`1` if we are outside of the quotes, `0` otherwise
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
	return (if_odd(pair[0]) == false && if_odd(pair[1]) == false);
}

/**
* @brief	Function that checks if the first nonspace char is opening
* bracket
* @param	str string that coming from readline function
* @return	`1` if it is true, `0` otherwise
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
* @return	`1` if it is true, `0` otherwise
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
