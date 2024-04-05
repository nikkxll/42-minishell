/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_update.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnikifor <dnikifor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 12:45:53 by dnikifor          #+#    #+#             */
/*   Updated: 2024/04/04 23:54:54 by dnikifor         ###   ########.fr       */
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
 * @param	exit_status string that represents exit status of the 
 * previous command run
 * @return	@c `MALLOC_ERR` if malloc failure occured, @c `SUCCESS` otherwise
 */
int	get_prompt(char *folder_name, char **prompt, char *exit_status)
{
	int		len;

	len = ft_strlen(folder_name) + ft_strlen(exit_status) + PROMPT_STATIC_LEN;
	*prompt = ft_calloc(len + 1, sizeof(char));
	if (!*prompt)
	{
		free(folder_name);
		return (MALLOC_ERR);
	}
	ft_strlcat(*prompt, "\033[1;36me-bash \033[0m\033[1;35m", len);
	ft_strlcat(*prompt, folder_name, len);
	if (ft_strcmp(exit_status, "0") == 0)
		ft_strlcat(*prompt, "\033[0m [\033[1;32m", len);
	else
		ft_strlcat(*prompt, "\033[0m [\033[1;31m", len);
	ft_strlcat(*prompt, exit_status, len);
	ft_strlcat(*prompt, "\033[0m] $ ", len);
	return (SUCCESS);
}
