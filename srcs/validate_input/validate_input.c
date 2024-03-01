/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_input.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dshatilo <dshatilo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 15:41:05 by dshatilo          #+#    #+#             */
/*   Updated: 2024/03/01 16:35:55 by dshatilo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"


// validate_input <complete_cmd> ::=  <and_or> <newline>
// validate_and_or<and_or>       ::=  <pipeline> { ('&&' | '||') <pipeline> }        
// validate_pipeline<pipeline>     ::=  <command> { '|' <command> }
// validate_command<command>      ::=  <simple_cmd> | '(' <and_or> ')'
// validate_simple_command<simple_cmd>   ::=  { <redirect> } <word> { ( <redirect> | <word> ) }
// validate_redirect<redirect>     ::=  ( '<' | '>' | '<<' | '>>' ) <word>

// t_bool	validate_input(char *str)
// {
// 	int	pos;

// 	pos = 0;
// 	validate_and_or(str, &pos);
// 	return (true);
// }
