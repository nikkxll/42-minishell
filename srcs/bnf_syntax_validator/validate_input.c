/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_input.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dshatilo <dshatilo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 15:41:05 by dshatilo          #+#    #+#             */
/*   Updated: 2024/04/15 10:54:18 by dshatilo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

/**
 * @brief	Validates the syntax of an input string according to the BNF
 * syntax format logic. This function is responsible for ensuring the syntactic
 * correctness of the input string according to the specified Backus-Naur
 * Form (BNF) syntax format. Function calls for the blocks listed below in
 * accordance with its tier.
 * BNF form looks as follows:
 * @brief	- `<v_input>	::= <and_or> <newline>`
 * @brief	- `<and_or>		::= <pipeline> { ('&&' | '||') <pipeline> }`
 * @brief	- `<pipeline>	::= <command> { '|' <command> }`
 * @brief	- `<command>	::= <simple_cmd> | '(' <and_or> ')' {<redirect>}`
 * @brief	- `<simple_cmd>	::= {( <redirect> | <word> | "any" | 'any')}`
 * @brief	- `<redirect>	::= ( '<' | '>' | '<<' | '>>' ) <word>`
 * @param	str String obtained from the readline function
 * @return	@c `-1` if a memory allocation error occurs during processing,
 * @c `1` if the input string passes syntax validation, @c `0` if the input
 * string fails to meet the required conditions
 */
int	validate_input(char *str)
{
	char	*next_token;
	t_bool	status;

	status = true;
	while (ft_isspace(*str))
		str++;
	next_token = validate_and_or(str, &status);
	if (*next_token != NULL_TERM || status == false)
	{
		print_syntax_error(next_token);
		return (SYNTAX_ERROR);
	}
	return (SUCCESS);
}
