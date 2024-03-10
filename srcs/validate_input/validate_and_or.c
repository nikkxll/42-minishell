/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_and_or.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dshatilo <dshatilo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 16:08:20 by dshatilo          #+#    #+#             */
/*   Updated: 2024/03/10 21:33:29 by dshatilo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

// <v_input> 		::=  <and_or> <newline>
// <and_or>			::=  <pipeline> { ('&&' | '||') <pipeline> }
// <pipeline>		::=  <command> { '|' <command> }
// <command>		::=  <simple_cmd> | '(' <and_or> ')' {<redirect>}
// <simple_cmd>		::=  {( <redirect> | <word> | "any" | 'any')}
// <redirect>		::=  ( '<' | '>' | '<<' | '>>' ) <word>

char	*validate_and_or(char *str, t_bool *status)
{
	char	*next_token;
	char	*next_and_or;

	while (*str == SPACE)
		str++;
	next_token = validate_pipeline(str, status);
	if (next_token == str || *status == false)
		return (next_token);
	else if ((ft_strncmp("&&", next_token, 2) == 0
			|| ft_strncmp("||", next_token, 2) == 0))
	{
		next_token += 2;
		if (is_blank_string(next_token) == true)
		{
			*status = false;
			return (next_token);
		}
		next_and_or = next_token;
		next_token = validate_and_or(next_and_or, status);
		if (next_token == next_and_or)
			*status = false;
	}
	return (next_token);
}
