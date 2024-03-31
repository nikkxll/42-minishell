/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_update.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnikifor <dnikifor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 12:45:53 by dnikifor          #+#    #+#             */
/*   Updated: 2024/04/01 01:40:36 by dnikifor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

/**
 * @brief	Getting current working directory
 * @param	folder_name pointer to string to fill with cwd
 * @return	@c `MALLOC_ERR` if malloc failure occured, @c `SUCCESS` otherwise
 */
int	get_current_folder_name(char **folder_name)
{
	char	*cwd;
	
    cwd = getcwd(NULL, 0);
    if (cwd)
	{
        *folder_name = ft_strdup(ft_strrchr(cwd, SLASH));
		if (!(*folder_name))
		{
			free(cwd);
			return (MALLOC_ERR);
		}
		free(cwd);
        return (SUCCESS);
    }
    return (MALLOC_ERR);
}

/**
 * @brief	Function that builds the full prompt
 * @param	folder_name current working directory
 * @param	prompt prompt to fill with info
 * @return	@c `MALLOC_ERR` if malloc failure occured, @c `SUCCESS` otherwise
 */
int	get_prompt(char *folder_name, char **prompt)
{
	char	*s1;
	char	*s2;
	
	s1 = ft_strjoin("", "\033[1;36me-bash \033[0m\033[1;35m");
	if (!s1)
	{
		free(folder_name);
		return (MALLOC_ERR);
	}
	s2 = ft_strjoin(s1, folder_name);
	free(folder_name);
	free(s1);
	if (!s2)
		return (MALLOC_ERR);
	*prompt = ft_strjoin(s2, "\033[0m $ ");
	free(s2);
	if (!(*prompt))
		return (MALLOC_ERR);
    return (SUCCESS);
}
