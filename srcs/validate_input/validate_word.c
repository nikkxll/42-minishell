/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_word.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dshatilo <dshatilo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 16:19:51 by dshatilo          #+#    #+#             */
/*   Updated: 2024/03/10 21:50:34 by dshatilo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

// v_input <complete_cmd> 		::=  <and_or> <newline>
// v_and_or<and_or>				::=  <pipeline> { ('&&' | '||') <pipeline> }
// v_pipeline<pipeline>			::=  <command> { '|' <command> }
// v_command<command>			::=  <simple_cmd> | '(' <and_or> ')'
// v_simple_command<simple_cmd>	::=  {( <redirect> | <word> | "any" | 'any')}
// v_redirect<redirect>			::=  ( '<' | '>' | '<<' | '>>' ) <word>

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
