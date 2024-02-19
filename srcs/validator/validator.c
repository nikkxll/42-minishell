/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validator.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnikifor <dnikifor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 13:42:57 by dnikifor          #+#    #+#             */
/*   Updated: 2024/02/19 17:55:08 by dnikifor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

int	validate_input_string(char *str)
{
	if (check_if_round_brackets_num_is_even(str, 0, 0, 0)
		&& !check_if_quotes_num_is_even(str, D_QUOTE, 0, 0)
		&& !check_if_quotes_num_is_even(str, S_QUOTE, 0, 0)
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

	char str[1000] = "echo '<<<' '()' k";
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
