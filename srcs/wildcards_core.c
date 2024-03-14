/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards_core.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnikifor <dnikifor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 01:01:56 by dnikifor          #+#    #+#             */
/*   Updated: 2024/03/15 01:15:50 by dnikifor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

static t_bool if_only_stars(char *pattern)
{
    while (*pattern)
    {
        if (*pattern++ != '*')
            return (false);
    }
    return (true);
}

static t_bool   process_pattern_match(char **line, char **pattern,
    t_bool *wildcard, char **placeholder)
{
    if (**pattern == **line)
    {
        (*line)++;
        (*pattern)++;
    }
    else if (**pattern == ASTERISK)
    {
        if (*(++(*pattern)) == NULL_TERM)
            return (true);
        *placeholder = *pattern;
        *wildcard = true;
    }
    else if (*wildcard)
    {
        if (*pattern == *placeholder)
            (*line)++;
        else
            *pattern = *placeholder;
    } 
    else
        return (false);
    return (false);
}

t_bool wildcard_strcmp(char *line, char *pattern)
{
    t_bool  wildcard;
    char    *placeholder;

    wildcard = false;
    while (*line)
    {
        if (process_pattern_match(&line, &pattern, &wildcard, &placeholder))
            return (true);
    }
    if (*pattern == NULL_TERM || if_only_stars(pattern))
        return (true);
    else
        return (false);
}
