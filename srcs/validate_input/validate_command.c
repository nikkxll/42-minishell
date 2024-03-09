/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_command.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dshatilo <dshatilo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 16:08:20 by dshatilo          #+#    #+#             */
/*   Updated: 2024/03/09 11:48:22 by dshatilo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

// <v_input> 		::=  <and_or> <newline>
// <and_or>			::=  <pipeline> { ('&&' | '||') <pipeline> }
// <pipeline>		::=  <command> { '|' <command> }
// <command>		::=  <simple_cmd> | '(' <and_or> ')' {<redirect>}
// <simple_cmd>		::=  {( <redirect> | <word> | "any" | 'any')}
// <redirect>		::=  ( '<' | '>' | '<<' | '>>' ) <word>

char	*validate_command(char *str, t_bool *status)
{
	char	*next_token;

	if (*status == false)
		return (str);
	while (*str == SPACE)
		str++;
	next_token = validate_simple_command(str);
	if (next_token != str)
		return (next_token);
	else if (*str == O_ROUND && is_blank_string(str + 1) == false)
	{
		next_token = validate_and_or(str + 1, status);
		if (next_token == str + 1)
			return (str);
		if (*next_token != C_ROUND)
		{
			*status = false;
			return (next_token);
		}
		next_token++;
		while (*next_token == SPACE)
			next_token++;
		next_token = validate_redirect(next_token);
	}
	return (next_token);
}
