/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnikifor <dnikifor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 13:19:28 by dshatilo          #+#    #+#             */
/*   Updated: 2024/03/12 13:58:29 by dnikifor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

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

char	**wrapper_ft_split_with_quotes(char *str)
{
	char	**res;
	int		i;

	i = 0;
	while (str[i] != NULL_TERM)
	{
		if (str[i] == SPACE)
			str[i] = SEPARATOR;
		else if (str[i] == D_QUOTE || str[i] == S_QUOTE)
			i += skip_quotes(str + i);
		i++;
	}
	res = ft_split(str, SEPARATOR);
	free(str);
	return (res);
}
