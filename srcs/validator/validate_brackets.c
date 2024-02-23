/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_brackets.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnikifor <dnikifor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 17:51:19 by dnikifor          #+#    #+#             */
/*   Updated: 2024/02/23 13:25:07 by dnikifor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

/**
* @brief	Checks if the number of round brackets which are outside of
* the quotes is even and number of opening are equal to the number of closing
* @param	str string that coming from readline function
* @param	point number to decrease until
* @param	key indicator of opening and closing brackets
* @param	quote_type int that tracks if we are within a quotes or not
* @return	if number of opening and closing brackets don't match return is 0,
* otherwise return is not 0
*/
int	check_if_round_brackets_num_is_even(char *str, int point,
	int key, int quote_type)
{
	int	i;

	i = (int)ft_strlen(str) - 1;
	while (i >= point)
	{
		check_if_inside_quotes(str, &i, &quote_type);
		if (!quote_type)
		{
			if (str[i] == O_ROUND)
				key++;
			if (str[i] == C_ROUND)
				key--;
			if (key > 0)
				return (!key);
			i--;
		}
		else
			i--;
	}
	return (!key);
}

/**
* @brief	Checks if there are two consecutive (opening and closing)
* round braces outside of the quotes
* @param	str string that coming from readline function
* @param	key indicator of opening and closing brackets
* @param	quote_type int that tracks if we are within a quotes or not
* @return	if key is more than 0 return is true, otherwise false
*/
int	two_consecutive_round_brackets_check(char *str, int key, int quote_type)
{
	int	i;

	i = 0;
	while (str[i] != NULL_TERM)
	{
		check_if_inside_quotes(str, &i, &quote_type);
		if (!quote_type)
		{
			if (str[i] == O_ROUND && str[i + 1] == C_ROUND)
				key++;
			i++;
		}
		else
			i++;
	}
	return (key > 0);
}
