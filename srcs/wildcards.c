/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnikifor <dnikifor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 22:16:41 by dnikifor          #+#    #+#             */
/*   Updated: 2024/03/14 00:00:05 by dnikifor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"
#include <dirent.h>

typedef struct dirent   t_dirent;

// hii*fcdj*ec
int check_entity(char *entity, char **str, int i, int j)
{
    while (str[0][i] != '*' && str[0][i] != NULL_TERM)
        i++;
    if (str[0][i] == '*')
    {
        if (!ft_strncmp(str[0], entity, i - j))
        {
            j = i;
            check_entity(entity, str, ++i, ++j);
        }
        else
            return (0);
    }
    else
    {
        if (!ft_strncmp(str[0], entity, i - j))
            return (1);
    }
    return (1);
}

// int iterate_through_entities(char **str)
// {
//     DIR         *dir;
//     t_dirent    *ent;
    
//     if ((dir = opendir(".")) != NULL)
//     {
//         while ((ent = readdir(dir)) != NULL)
//         {
//             if (check_entity(ent->d_name, str, 0, 0))
//                 add_to_string();
//         }
//         closedir(dir);
//     } 
//     else
//     {
//         perror("Unable to open directory");
//         return (1);
//     }
// }

int wildcards(char **str)
{
    if (check_entity("minishell", str, 0, 0))
        printf("%s\n", "fine!!");
    // iterate_through_entities(str);
    return (0);
}
