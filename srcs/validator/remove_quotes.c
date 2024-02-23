/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnikifor <dnikifor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 17:53:22 by dnikifor          #+#    #+#             */
/*   Updated: 2024/02/23 13:25:18 by dnikifor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

/**
* @brief	Removes consecutive quotes from the string is allowable
* @param	str - string that coming from readline function
*/
void	remove_quotes(char *str)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (str[i] != NULL_TERM)
	{
		if ((str[i] == S_QUOTE && str[i + 1] == D_QUOTE
				&& str[i + 2] == D_QUOTE && str[i + 3] == S_QUOTE)
			|| (str[i] == D_QUOTE && str[i + 1] == S_QUOTE
				&& str[i + 2] == S_QUOTE && str[i + 3] == D_QUOTE))
		{
			str[j++] = str[i + 1];
			str[j++] = str[i + 2];
			i += 4;
		}
		else if ((str[i] == S_QUOTE && str[i + 1] == S_QUOTE)
			|| (str[i] == D_QUOTE && str[i + 1] == D_QUOTE))
			i += 2;
		else
			str[j++] = str[i++];
	}
	str[j] = NULL_TERM;
}
