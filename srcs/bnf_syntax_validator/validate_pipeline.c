/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_pipeline.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dshatilo <dshatilo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 16:08:20 by dshatilo          #+#    #+#             */
/*   Updated: 2024/04/15 10:41:02 by dshatilo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

char	*validate_pipeline(char *str, t_bool *status)
{
	char	*next_token;

	while (ft_isspace(*str))
		str++;
	next_token = validate_command(str, status);
	if (next_token == str)
		*status = false;
	if (*status == false)
		return (next_token);
	else if (*next_token == PIPE && next_token[1] != PIPE)
	{
		next_token++;
		if (is_blank_string(next_token) == true)
		{
			*status = false;
			return (next_token);
		}
		next_token = validate_pipeline(next_token, status);
	}
	return (next_token);
}
