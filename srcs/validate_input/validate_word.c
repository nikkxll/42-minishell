/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_word.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnikifor <dnikifor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 16:19:51 by dshatilo          #+#    #+#             */
/*   Updated: 2024/03/26 19:08:44 by dnikifor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

// <v_input> 		::=  <and_or> <newline>
// <and_or>			::=  <pipeline> { ('&&' | '||') <pipeline> }
// <pipeline>		::=  <command> { '|' <command> }
// <command>		::=  <simple_cmd> | '(' <and_or> ')' {<redirect>}
// <simple_cmd>		::=  {( <redirect> | <word> | "any" | 'any')}
// <redirect>		::=  ( '<' | '>' | '<<' | '>>' ) <word>

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
