/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_pipeline.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dshatilo <dshatilo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 16:08:20 by dshatilo          #+#    #+#             */
/*   Updated: 2024/03/06 11:46:45 by dshatilo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

// validate_pipeline<pipeline>     ::=  <command> { '|' <command> }
// validate_command<command>      ::=  <simple_cmd> | '(' <and_or> ')' { <redirect> }
// validate_simple_command<simple_cmd>   ::=  { <redirect> } <word> { ( <redirect> | <word> ) }
// validate_redirect<redirect>     ::=  ( '<' | '>' | '<<' | '>>' ) <word>

char	*validate_pipeline(char *str)
{
	char	*next_token;

	while (*str == SPACE)
		str++;
	next_token = validate_command(str);
	if (next_token == str)
		return (next_token);
	else if (*next_token == PIPE && next_token[1] != PIPE
		&& is_blank_string(next_token + 1) == false)
		next_token = validate_pipeline(next_token + 1);
	return (next_token);
}
