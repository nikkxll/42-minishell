/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_simple_command.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dshatilo <dshatilo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 16:08:20 by dshatilo          #+#    #+#             */
/*   Updated: 2024/04/15 10:59:25 by dshatilo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

char	*validate_simple_command(char *str, t_bool *status)
{
	char	*next_token;

	while (ft_isspace(*str))
		str++;
	next_token = validate_redirect(str, status);
	if (next_token == str)
		next_token = validate_word(str, status);
	if (*status == false || *next_token == C_ROUND)
		return (next_token);
	if (next_token != str)
		next_token = validate_simple_command(next_token, status);
	return (next_token);
}
