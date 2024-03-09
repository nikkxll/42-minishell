/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_and_or.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dshatilo <dshatilo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 16:08:20 by dshatilo          #+#    #+#             */
/*   Updated: 2024/03/09 11:37:57 by dshatilo         ###   ########.fr       */
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
	int		i;

	if (*status == false)
		return (str);
	while (*str == SPACE)
		str++;
	next_token = validate_pipeline(str, status);
	if (next_token == str)
		return (next_token);
	else if ((ft_strncmp("&&", next_token, 2) == 0
			|| ft_strncmp("||", next_token, 2) == 0)
		&& is_blank_string(next_token + 2) == false)
	{
		i = 2;
		while (next_token[i] == SPACE)
			i++;
		next_and_or = validate_and_or(next_token + i, status);
		if (next_and_or == next_token + i)
			return (next_token);
		return (next_and_or);
	}
	return (next_token);
}
