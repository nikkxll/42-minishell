/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_redirect.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnikifor <dnikifor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 16:08:20 by dshatilo          #+#    #+#             */
/*   Updated: 2024/04/08 17:45:49 by dnikifor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

char	*validate_redirect(char *str, t_bool *status)
{
	char	*next_token;

	if (ft_strncmp(">>", str, 2) == 0)
		str += 2;
	else if (ft_strncmp("<<", str, 2) == 0)
		str += 2;
	else if (ft_strncmp(">", str, 1) == 0)
		str += 1;
	else if (ft_strncmp("<", str, 1) == 0)
		str += 1;
	else
		return (str);
	while (ft_isspace(*str))
		str++;
	next_token = validate_word(str, status);
	if (next_token == str)
		*status = false;
	if (*status == false || *next_token == C_ROUND)
		return (next_token);
	while (ft_isspace(*next_token))
		next_token++;
	next_token = validate_redirect(next_token, status);
	return (next_token);
}
