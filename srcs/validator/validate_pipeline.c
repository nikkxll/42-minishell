/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_pipeline.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dshatilo <dshatilo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 16:08:20 by dshatilo          #+#    #+#             */
/*   Updated: 2024/04/07 00:28:00 by dshatilo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

// <v_input> 		::=  <and_or> <newline>
// <and_or>			::=  <pipeline> { ('&&' | '||') <pipeline> }
// <pipeline>		::=  <command> { '|' <command> }
// <command>		::=  <simple_cmd> | '(' <and_or> ')' {<redirect>}
// <simple_cmd>		::=  {( <redirect> | <word> | "any" | 'any')}
// <redirect>		::=  ( '<' | '>' | '<<' | '>>' ) <word>

char	*validate_pipeline(char *str, t_bool *status)
{
	char	*next_token;
	char	*next_pipeline;

	while (ft_isspace(*str))
		str++;
	next_token = validate_command(str, status);
	if (next_token == str || *status == false)
		return (next_token);
	else if (*next_token == PIPE && next_token[1] != PIPE)
	{
		next_token++;
		if (is_blank_string(next_token) == true)
		{
			*status = false;
			return (next_token);
		}
		while (ft_isspace(*next_token))
			next_token++;
		next_pipeline = next_token;
		next_token = validate_pipeline(next_pipeline, status);
		if (next_token == next_pipeline)
			*status = false;
	}
	return (next_token);
}
