/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_redirect.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dshatilo <dshatilo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 16:08:20 by dshatilo          #+#    #+#             */
/*   Updated: 2024/03/08 10:57:26 by dshatilo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

// <v_input> 		::=  <and_or> <newline>
// <and_or>			::=  <pipeline> { ('&&' | '||') <pipeline> }
// <pipeline>		::=  <command> { '|' <command> }
// <command>		::=  <simple_cmd> | '(' <and_or> ')' {<redirect>}
// <simple_cmd>		::=  {( <redirect> | <word> | "any" | 'any')}
// <redirect>		::=  ( '<' | '>' | '<<' | '>>' ) <word>

char	*validate_redirect(char *str)
{
	char	*next_token;
	int		i;

	i = 0;
	if (ft_strncmp(">>", str, 2) == 0)
		i += 2;
	else if (ft_strncmp("<<", str, 2) == 0)
		i += 2;
	else if (ft_strncmp(">", str, 1) == 0)
		i += 1;
	else if (ft_strncmp("<", str, 1) == 0)
		i += 1;
	else
		return (str);
	while (str[i] == SPACE)
		i++;
	next_token = validate_word(str + i);
	if (next_token == str + i)
		return (str);
	i = 0;
	while (next_token[i] == SPACE)
		i++;
	str = validate_redirect(next_token + i);
	return (str);
}
