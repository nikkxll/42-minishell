/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_word.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dshatilo <dshatilo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 16:19:51 by dshatilo          #+#    #+#             */
/*   Updated: 2024/04/15 10:59:29 by dshatilo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

static char	*validate_quotes(char *str, t_bool *status);

char	*validate_word(char *str, t_bool *status)
{
	char	*special_characters;

	special_characters = "&|<>() '\"";
	while (*str && ft_strchr(special_characters, *str) == NULL)
		str++;
	if (*str == S_QUOTE || *str == D_QUOTE)
		str = validate_quotes(str, status);
	return (str);
}

static char	*validate_quotes(char *str, t_bool *status)
{
	if (*str == D_QUOTE)
	{
		str++;
		while (*str != NULL_TERM && *str != D_QUOTE)
			str++;
	}
	else if (*str == S_QUOTE)
	{
		str++;
		while (*str != NULL_TERM && *str != S_QUOTE)
			str++;
	}
	if (*str == NULL_TERM)
	{
		*status = false;
		return (str);
	}
	return (str + 1);
}
