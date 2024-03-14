/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnikifor <dnikifor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 22:16:41 by dnikifor          #+#    #+#             */
/*   Updated: 2024/03/14 12:28:44 by dnikifor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"
#include <dirent.h>

typedef struct dirent   t_dirent;

// minishell
// m*s**j*
t_bool check_entity(char *entity, char *str, t_bool last_sym)
{
    char    *new_str_pos;
    int     i;
    int     j;
    
    i = 0;
    j = 0;
    while (str[i] == ASTERISK && str[i] != NULL_TERM)
        i++;
    if (str[i] != NULL_TERM)
    {
        j = i;
        while (str[j] != ASTERISK && str[j] != NULL_TERM)
            j++;
        str[j] = NULL_TERM;
        new_str_pos = ft_strnstr(entity, str + i, ft_strlen(entity));
        if (new_str_pos)
            return (check_entity(new_str_pos + (j - i), str + j + 1, last_sym));
        else
            return (false);
    }
    else if (*entity == NULL_TERM || last_sym)
        return (true);
    else
        return (false);
    return (true);
}

t_bool is_last_asterisk(char *new_str)
{
    return (new_str[ft_strlen(new_str) - 1] == ASTERISK);
}

int wildcards(char **str)
{
    char    *new_str;

    new_str = *str;
    if (check_entity("minishell", new_str, is_last_asterisk(new_str)))
        printf("%s\n", "fine!!");
    else
        printf("%s\n", "nope!!");
    // iterate_through_entities(str);
    return (0);
}
