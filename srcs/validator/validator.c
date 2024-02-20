/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validator.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnikifor <dnikifor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 13:42:57 by dnikifor          #+#    #+#             */
/*   Updated: 2024/02/20 17:41:18 by dnikifor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

/*
* Validates input string which is coming from prompt
* Consists of checks for different meta characters, quotes, parenthesis etc
*
* Input:
* - `str` - string that coming from readline function
* 
* Output:
* - `0` (VALID) or `1` (INVALID), status that corresponds to the result of
* validation
*/
int	validate_input_string(char *str)
{
	if (check_if_round_brackets_num_is_even(str, 0, 0, 0)
		&& !two_consecutive_round_brackets_check(str, 0, 0)
		&& !check_if_redirects_and_or_are_correct(str, REDIR_L, REDIR_R, 0)
		&& !check_if_redirects_and_or_are_correct(str, PIPE, AND, 0)
		&& !check_if_redirect_file_pattern_complied(str, 0, 0)
		&& !check_if_backslash_or_semicolon_exist(str, 0))
	{
		remove_quotes(str);
		return (VALID);
	}
	else
		return (INVALID);
}

int	main(void)
{
	int	status;
 
	char str[1000] = "ec""h''o 1";
	status = validate_input_string(str);
	if (status)
	{
		printf("%s\n", "INVALID");
		printf("%s\n", str);
	}
	else
	{
		printf("%s\n", "VALID");
		printf("%s\n", str);
	}

}
