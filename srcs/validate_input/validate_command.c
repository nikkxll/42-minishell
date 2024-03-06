/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_command.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dshatilo <dshatilo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 16:08:20 by dshatilo          #+#    #+#             */
/*   Updated: 2024/03/06 11:47:20 by dshatilo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

// validate_command<command>      ::=  <simple_cmd> | '(' <and_or> ')'
// validate_simple_command<simple_cmd>   ::=  {( <redirect> | <word> | "anything" | 'anything')}
// validate_redirect<redirect>     ::=  ( '<' | '>' | '<<' | '>>' ) <word>

char	*validate_command(char *str)
{
	char	*next_token;
	char	*and_or;

	while (*str == SPACE)
		str++;
	next_token = validate_simple_command(str);
	if (next_token != str)
		return (next_token);
	else if (*next_token == O_ROUND && is_blank_string(next_token + 1) == false)
	{
		and_or = validate_and_or(next_token + 1);
		if (*and_or != C_ROUND)
			return (next_token);
		else
			next_token = and_or + 1;
		next_token = validate_redirect(next_token);
	}
	return (next_token);
}
