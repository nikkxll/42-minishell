/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_update.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dshatilo <dshatilo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 12:45:53 by dnikifor          #+#    #+#             */
/*   Updated: 2024/08/23 13:04:24 by dshatilo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

int	build_prompt(char *folder_name, char **prompt, char *exit_status);

/**
 * @brief	Getting current working directory
 * @param	prompt pointer to the prompt string
 * @param	exit_status exit_status of previous run
 * @return	@c `MALLOC_ERR` if malloc failure occured, @c `status` otherwise
 */
int	get_prompt(char **prompt, int exit_status)
{
	char	*cwd;
	char	*folder_name;
	int		status;
	char	*es;

	es = ft_itoa(exit_status);
	if (!es)
		return (MALLOC_ERR);
	cwd = getcwd(NULL, 0);
	if (!cwd)
		folder_name = "";
	else
		folder_name = ft_strrchr(cwd, SLASH);
	status = build_prompt(folder_name, prompt, es);
	if (cwd)
		free(cwd);
	free(es);
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
	ft_strlcat(*prompt, "d-sh ", len);
	ft_strlcat(*prompt, folder_name, len);
	ft_strlcat(*prompt, " [", len);
	ft_strlcat(*prompt, exit_status, len);
	ft_strlcat(*prompt, "] $ ", len);
	return (SUCCESS);
}
