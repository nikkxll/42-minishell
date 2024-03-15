/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards_core.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnikifor <dnikifor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 01:01:56 by dnikifor          #+#    #+#             */
/*   Updated: 2024/03/15 16:09:16 by dnikifor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

static int	process_pattern_match(char **line, char **pattern,
	t_bool *wildcard, char **placeholder)
{
	if (**pattern == **line)
	{
		(*line)++;
		(*pattern)++;
		return (0);
	}
	else if (**pattern == ASTERISK)
	{
		if (*(++(*pattern)) == NULL_TERM)
			return (1);
		*placeholder = *pattern;
		*wildcard = true;
		return (0);
	}
	else if (*wildcard)
	{
		if (*pattern == *placeholder)
			(*line)++;
		else
			*pattern = *placeholder;
		return (0);
	}
	else
		return (-1);
}

t_bool	wildcard_strcmp(char *line, char *pattern)
{
	int		status;
	char	*placeholder;
	t_bool	wildcard;

	status = 0;
	placeholder = NULL;
	wildcard = false;
	string_quotes_transform(line, pattern);
	while (*line)
	{
		status = process_pattern_match(&line, &pattern, &wildcard, &placeholder);
		if (status == 1)
		{
			string_quotes_transform_back(line, pattern);
			return (true);
		}
		else if (status == -1)
		{
			string_quotes_transform_back(line, pattern);
			return (false);
		}
	}
	if (*pattern == NULL_TERM || if_only_asterisk(pattern))
		return (true);
	else
		return (false);
	string_quotes_transform_back(line, pattern);
}
