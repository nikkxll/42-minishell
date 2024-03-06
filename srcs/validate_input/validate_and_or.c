/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_and_or.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dshatilo <dshatilo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 16:08:20 by dshatilo          #+#    #+#             */
/*   Updated: 2024/03/06 10:48:02 by dshatilo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

// validate_and_or<and_or>       ::=  <pipeline> { ('&&' | '||') <pipeline> }        
// validate_pipeline<pipeline>     ::=  <command> { '|' <command> }
// validate_command<command>      ::=  <simple_cmd> | '(' <and_or> ')'
// validate_simple_command<simple_cmd>   ::=  { <redirect> } <word> { ( <redirect> | <word> ) }
// validate_redirect<redirect>     ::=  ( '<' | '>' | '<<' | '>>' ) <word>


char	*validate_and_or(char *str)
{
	char	*next_token;

	while (*str == SPACE)
		str++;
	next_token = validate_pipeline(str);
	if (next_token == str)
		return (next_token);
	else if ((ft_strncmp("&&", next_token, 2) == 0
			|| ft_strncmp("||", next_token, 2) == 0)
		&& is_blank_string(next_token + 2) == false)
		next_token = validate_and_or(next_token + 2);
	return (next_token);
}
