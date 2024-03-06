/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_word.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dshatilo <dshatilo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 16:19:51 by dshatilo          #+#    #+#             */
/*   Updated: 2024/03/06 17:47:45 by dshatilo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

char	*validate_quotes(char *str);

char	*validate_word(char *str)
{
	char	*special_characters;

	special_characters = "&|<>() '\"\n";
	while (*str && ft_strchr(special_characters, *str) == NULL)
		str++;
	if (*str == S_QUOTE || *str == D_QUOTE)
		str = validate_quotes(str);
	return (str);
}

char	*validate_quotes(char *str)
{
	int		i;
	char	*curr;

	i = 0;
	curr = str;
	if (curr[i] == D_QUOTE)
	{
		i++;
		while (curr[i] != NULL_TERM && curr[i] != D_QUOTE)
			i++;
	}
	else if (curr[i] == S_QUOTE)
	{
		i++;
		while (curr[i] != NULL_TERM && curr[i] != S_QUOTE)
			i++;
	}
	else
		return (str);
	if (curr[i] == NULL_TERM)
		return ("\n");
	else
		return (curr + i + 1);
}
