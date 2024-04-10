/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_update.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnikifor <dnikifor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 12:45:53 by dnikifor          #+#    #+#             */
/*   Updated: 2024/04/10 18:32:53 by dnikifor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

int	build_prompt(char *folder_name, char **prompt, char *exit_status);

/**
 * @brief	Getting current working directory
 * @param	folder_name pointer to string to fill with cwd
 * @param	exit_status exit_status of previous run
 * @return	@c `MALLOC_ERR` if malloc failure occured, @c `status` otherwise
 */
int	get_prompt(char **prompt, int exit_status)
{
	char	*cwd;
	char	*folder_name;
	int		status;
	char	*es;

	cwd = getcwd(NULL, 0);
	if (!cwd)
		return (GETCWD_ERROR);
	folder_name = ft_strdup(ft_strrchr(cwd, SLASH));
	free(cwd);
	if (!(*folder_name))
		return (MALLOC_ERR);
	es = ft_itoa(exit_status);
	if (!es)
	{
		free(folder_name);
		return (MALLOC_ERR);
	}
	status = build_prompt(folder_name, prompt, es);
	free(es);
	free(folder_name);
	return (status);
}

/**
 * @brief	Function that builds the full prompt
 * @param	folder_name current working directory
 * @param	prompt prompt to fill with info
 * @param	exit_status string that represents exit status of the 
 * previous command run
 * @return	@c `MALLOC_ERR` if malloc failure occured, @c `SUCCESS` otherwise
 */
int	build_prompt(char *folder_name, char **prompt, char *exit_status)
{
	int		len;

	len = ft_strlen(folder_name) + ft_strlen(exit_status) + PROMPT_STATIC_LEN;
	*prompt = ft_calloc(len + 1, sizeof(char));
	if (!*prompt)
		return (MALLOC_ERR);
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
