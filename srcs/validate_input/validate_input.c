/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_input.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dshatilo <dshatilo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 15:41:05 by dshatilo          #+#    #+#             */
/*   Updated: 2024/03/06 17:42:31 by dshatilo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"


// validate_input <complete_cmd> ::=  <and_or> <newline>
// validate_and_or<and_or>       ::=  <pipeline> { ('&&' | '||') <pipeline> }        
// validate_pipeline<pipeline>     ::=  <command> { '|' <command> }
// validate_command<command>      ::=  <simple_cmd> | '(' <and_or> ')'
// validate_simple_command<simple_cmd>   ::=  {( <redirect> | <word> | "anything" | 'anything')}
// validate_redirect<redirect>     ::=  ( '<' | '>' | '<<' | '>>' ) <word>

t_bool	validate_input(char *str)
{
	char	*next_token;

	next_token = validate_and_or(str);
	if (*next_token != NULL_TERM)
	{
		ft_putstr_fd("e-bash: syntax error near unexpected token `", 2);
		if (*next_token == NL)
			ft_putstr_fd("newline", 2);
		else
			ft_putstr_fd(next_token, 2);
		ft_putendl_fd("'", 2);
		return (false);
	}
	return (true);
}
