/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_brackets.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnikifor <dnikifor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 17:51:19 by dnikifor          #+#    #+#             */
/*   Updated: 2024/02/19 19:01:51 by dnikifor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

/*
* Checks if the number of round brackets which are outside of the quotes is
* even and number of opening are equal to the number of closing
* Input:
* - `str` - string that coming from readline function
* - `point` - number to decrease until
* - `key` - indicator of opening and closing brackets
* - `quote_type` - int that tracks if we are within a quotes or not
* 
* Output:
* - if number of opening and closing brackets don't match return is 0,
* otherwise return is not 0
*/
int	check_if_round_brackets_num_is_even(char *str, int point,
	int key, int quote_type)
{
	int	i;

	i = (int)ft_strlen(str) - 1;
	while (i >= point)
	{
		check_if_inside_quotes_with_decr(str, &i, &quote_type);
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

/*
* Checks if there are two consecutive (opening and closing) round braces
* outside of the quotes
* Input:
* - `str` - string that coming from readline function
* - `key` - indicator of opening and closing brackets
* - `quote_type` - int that tracks if we are within a quotes or not
* 
* Output:
* - if key is more than 0 return is true, otherwise false
*/
int	two_consecutive_round_brackets_check(char *str, int key, int quote_type)
{
	int	i;

	i = 0;
	while (str[i] != NULL_TERM)
	{
		check_if_inside_quotes_with_incr(str, &i, &quote_type);
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
