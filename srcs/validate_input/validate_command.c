/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_command.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dshatilo <dshatilo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 16:08:20 by dshatilo          #+#    #+#             */
/*   Updated: 2024/03/08 19:02:11 by dshatilo         ###   ########.fr       */
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

	while (*str == SPACE)
		str++;
	next_token = validate_simple_command(str);
	if (next_token != str)
		return (next_token);
	else if (*next_token == O_ROUND && is_blank_string(next_token + 1) == false)
		;
	return (next_token);
}

// else if (*next_token == O_ROUND && is_blank_string(next_token + 1) == false)
// 	{
// 		i = 1;
// 		while (next_token[i] == SPACE)
// 			i++;
// 		and_or = validate_and_or(next_token + i);
// 		if (and_or == next_token + i)
// 			return (next_token);
// 		if (*and_or != C_ROUND)
// 			return (next_token);
// 		else
// 			next_token = and_or + 1;
// 		while (*next_token == SPACE)
// 			next_token++;
// 		next_token = validate_redirect(next_token);
// 	}
// 	return (next_token);