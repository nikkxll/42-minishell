/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_if_inside_quotes.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnikifor <dnikifor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 12:42:41 by dshatilo          #+#    #+#             */
/*   Updated: 2024/04/01 01:39:54 by dnikifor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../headers/minishell.h"

/**
 * @brief	Auxiliary function that checks if we are inside of the quotes
 * @param	str string that coming from readline function
 * @param	i pointer to the index to increment
 * @param	quote_type pointer to the int that tracks if we are within
 * the quotes or not
 * @return	@c `void`
 */
void	check_if_inside_quotes(char *str, int *i, int *quote_type)
{
	if (str[*i] == S_QUOTE && *quote_type == S_QUOTE)
		*quote_type = 0;
	else if (str[*i] == S_QUOTE && *quote_type == 0)
		*quote_type = S_QUOTE;
	else if (str[*i] == D_QUOTE && *quote_type == D_QUOTE)
		*quote_type = 0;
	else if (str[*i] == D_QUOTE && *quote_type == 0)
		*quote_type = D_QUOTE;
}
