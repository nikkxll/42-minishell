/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_pipeline.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dshatilo <dshatilo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 16:08:20 by dshatilo          #+#    #+#             */
/*   Updated: 2024/03/06 19:10:58 by dshatilo         ###   ########.fr       */
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
	char	*pipeline;
	int		i;

	while (*str == SPACE)
		str++;
	next_token = validate_command(str);
	if (next_token == str)
		return (next_token);
	else if (*next_token == PIPE && next_token[1] != PIPE
		&& is_blank_string(next_token + 1) == false)
	{
		i = 1;
		while (next_token[i] == SPACE)
			i++;
		pipeline = validate_pipeline(next_token + i);
		if (pipeline == next_token + i)
			return (next_token);
	}
	return (next_token);
}
