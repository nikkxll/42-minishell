/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_input.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnikifor <dnikifor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 15:41:05 by dshatilo          #+#    #+#             */
/*   Updated: 2024/04/02 14:00:39 by dnikifor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

// <v_input> 		::=  <and_or> <newline>
// <and_or>			::=  <pipeline> { ('&&' | '||') <pipeline> }
// <pipeline>		::=  <command> { '|' <command> }
// <command>		::=  <simple_cmd> | '(' <and_or> ')' {<redirect>}
// <simple_cmd>		::=  {( <redirect> | <word> | "any" | 'any')}
// <redirect>		::=  ( '<' | '>' | '<<' | '>>' ) <word>

t_bool	validate_input(char *str)
{
	char	*next_token;
	t_bool	status;

	if (is_blank_string(str) == true)
		return (true);
	status = true;
	while (*str == SPACE)
		str++;
	next_token = validate_and_or(str, &status);
	if (*next_token != NULL_TERM || status == false)
	{
		print_syntax_error(next_token);
		return (false);
	}
	return (true);
}

// int	main(int argc, char **argv)
// {
// 	if (argc != 2)
// 	{
// 		ft_printf("INCORRECT NUMBER OF ARGUMENTS!\n");
// 		return (1);
// 	}
// 	if (validate_input(argv[1]) == true)
// 		ft_printf("Input is correct!\n");
// 	(void)argc;
// 	return (0);
// }
