/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_pipeline.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dshatilo <dshatilo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 16:08:20 by dshatilo          #+#    #+#             */
/*   Updated: 2024/03/09 11:38:40 by dshatilo         ###   ########.fr       */
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
	int		i;

	if (*status == false)
		return (str);
	while (*str == SPACE)
		str++;
	next_token = validate_command(str, status);
	if (next_token == str)
		return (next_token);
	else if (*next_token == PIPE && next_token[1] != PIPE
		&& is_blank_string(next_token + 1) == false)
	{
		i = 1;
		while (next_token[i] == SPACE)
			i++;
		next_pipeline = validate_pipeline(next_token + i, status);
		if (next_pipeline == next_token + i)
			return (next_token);
		return (next_pipeline);
	}
	return (next_token);
}
