/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_simple_command.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dshatilo <dshatilo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 16:08:20 by dshatilo          #+#    #+#             */
/*   Updated: 2024/03/08 15:55:30 by dshatilo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

// <v_input> 		::=  <and_or> <newline>
// <and_or>			::=  <pipeline> { ('&&' | '||') <pipeline> }
// <pipeline>		::=  <command> { '|' <command> }
// <command>		::=  <simple_cmd> | '(' <and_or> ')' {<redirect>}
// <simple_cmd>		::=  {( <redirect> | <word> | "any" | 'any')}
// <redirect>		::=  ( '<' | '>' | '<<' | '>>' ) <word>

char	*validate_simple_command(char *str)
{
	char	*next_token;

	while (*str == SPACE)
		str++;
	next_token = validate_redirect(str);
	if (next_token == str)
		next_token = validate_word(str);
	if (next_token != str)
		next_token = validate_simple_command(next_token);
	return (next_token);
}
