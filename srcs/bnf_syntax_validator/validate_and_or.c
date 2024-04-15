/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_and_or.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dshatilo <dshatilo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 16:08:20 by dshatilo          #+#    #+#             */
/*   Updated: 2024/04/15 10:32:35 by dshatilo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

char	*validate_and_or(char *str, t_bool *status)
{
	char	*next_token;

	while (ft_isspace(*str))
		str++;
	next_token = validate_pipeline(str, status);
	if (*status == false)
		return (next_token);
	if ((ft_strncmp("&&", next_token, 2) == 0
			|| ft_strncmp("||", next_token, 2) == 0))
	{
		next_token += 2;
		if (is_blank_string(next_token) == true)
		{
			*status = false;
			return (next_token);
		}
		next_token = validate_and_or(next_token, status);
	}
	return (next_token);
}
