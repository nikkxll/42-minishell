/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_quotes.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnikifor <dnikifor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 17:49:58 by dnikifor          #+#    #+#             */
/*   Updated: 2024/02/19 19:02:58 by dnikifor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

/*
* Checks if the number of quotes (single or double) which are outside of 
* the quotes (single or double) is even
*
* Input:
* - `str` - string that coming from readline function
* - `type` - ASCII code of the quote (single or double)
* - `key` - checks number of quotes
* - `quote_type` - int that tracks if we are within a quotes or not
* 
* Output:
* - if number of quotes is not even return is 1, otherwise return is not 0
*/
int	check_if_quotes_num_is_even(char *str, int type, int key, int quote_type)
{
	int	i;
	int	len;

	i = 0;
	len = (int)ft_strlen(str);
	while (i < len)
	{
		check_if_inside_quotes_with_incr(str, &i, &quote_type);
		if (!quote_type)
		{
			if (str[i] == type)
				key++;
			i++;
		}
		else
			i++;
	}
	return (key % 2);
}
