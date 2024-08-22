/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_with_quotes.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnikifor <dnikifor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 13:19:28 by dshatilo          #+#    #+#             */
/*   Updated: 2024/08/22 13:03:15 by dnikifor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

/**
 * @brief	Auxiliary function for @c `wrapper_ft_split_with_quotes()` function
 * @param	str string to skip quotes in
 * @return	@c `i` - current position in the string
 */
static int	skip_quotes(char *str)
{
	int	i;

	i = 0;
	if (*str == D_QUOTE)
	{
		i++;
		while (str[i] != D_QUOTE)
			i++;
	}
	else if (*str == S_QUOTE)
	{
		i++;
		while (str[i] != S_QUOTE)
			i++;
	}
	return (i);
}

/**
 * @brief	Function that doing the same operation as original @c `ft_split`,
 * but doesn't consider spaces as separating characters within the
 * single or double quotes
 * @param	str string to skip quotes in
 * @return	split array
 */
char	**wrapper_ft_split_with_quotes(char *str)
{
	char	**res;
	int		i;

	i = 0;
	while (str[i] != NULL_TERM)
	{
		if (str[i] == SPCE || str[i] == HT)
			str[i] = SEPARATOR;
		else if (str[i] == D_QUOTE || str[i] == S_QUOTE)
			i += skip_quotes(str + i);
		i++;
	}
	res = ft_split(str, SEPARATOR);
	if (!res)
		return (NULL);
	return (res);
}
