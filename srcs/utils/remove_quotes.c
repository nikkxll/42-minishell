/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnikifor <dnikifor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 13:56:07 by dshatilo          #+#    #+#             */
/*   Updated: 2024/08/22 13:03:15 by dnikifor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

/**
 * @brief	Removes quotes from the string if allowable
 * @param	str string that coming from readline function
 * @param	i index
 * @param	j index
 * @return	@c `void`
 */
void	remove_quotes(char *str, int i, int j)
{
	int	len;
	int	inside_quotes;

	len = ft_strlen(str);
	inside_quotes = 0;
	while (i < len)
	{
		if ((str[i] == S_QUOTE || str[i] == D_QUOTE) && !inside_quotes)
			inside_quotes = str[i];
		else if (str[i] == S_QUOTE && inside_quotes == S_QUOTE)
			inside_quotes = 0;
		else if (str[i] == D_QUOTE && inside_quotes == D_QUOTE)
			inside_quotes = 0;
		else if (str[i] == SPCE && !inside_quotes)
			break ;
		else
			str[j++] = str[i];
		i++;
	}
	while (i < len)
		str[j++] = str[i++];
	str[j] = NULL_TERM;
}

/**
 * @brief	A function that runs @c `remove_quotes()` function in a loop
 * @param	arr array of arguments
 * @param	i an index
 * @return	@c `void`
 */
void	remove_quotes_arr(char **arr, int i)
{
	while (arr[i])
		remove_quotes(arr[i++], 0, 0);
}
