/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards_core.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnikifor <dnikifor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 01:01:56 by dnikifor          #+#    #+#             */
/*   Updated: 2024/03/26 19:28:23 by dnikifor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../headers/minishell.h"

/**
 * @brief	Function to process a single character match between a string
 * and a pattern
 * @note	This function compares a character from the string against the
 * corresponding character in the pattern and handles wildcard ('*') matches
 * @param	line Pointer to the current character in the input string
 * @param	pattern Pointer to the current character in the wildcard pattern
 * @param	wildcard Pointer to a boolean flag indicating whether a wildcard
 * character ('*') was encountered
 * @param	placeholder Pointer to a placeholder for potential substitution in
 * the pattern
 * @return	@c `0` if characters match or wildcard match is processed,
 * @c `1` if the pattern has been fully processed (reached the end with
 * wildcard), @c `-1` if there is a mismatch between characters and no
 * wildcard match
 */
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

/**
 * @brief	Function to compare a string against a wildcard pattern
 * @note	This function compares a given string against a wildcard pattern,
 * where '*' in the pattern matches any sequence of characters (including
 * an empty sequence)
 * @param	line The input string to be compared
 * @param	pattern The wildcard pattern to match against
 * @return	@c `true` if the string matches the pattern, @c `false` otherwise
 */
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
		status = process_pattern_match(&line, &pattern, &wildcard,
				&placeholder);
		if (status == 1)
			return (string_quotes_transform_back(line, pattern, true));
		else if (status == -1)
			return (string_quotes_transform_back(line, pattern, false));
	}
	if (*pattern == NULL_TERM || if_only_asterisk(pattern))
		return (string_quotes_transform_back(line, pattern, true));
	else
		return (string_quotes_transform_back(line, pattern, false));
}
