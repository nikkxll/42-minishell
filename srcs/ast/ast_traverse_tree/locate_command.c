/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   locate_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dshatilo <dshatilo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 00:57:59 by dshatilo          #+#    #+#             */
/*   Updated: 2024/04/01 01:59:43 by dshatilo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../headers/minishell.h"

int	get_path(char ***path, char **envp, char *cmd);

int	locate_command(char	**cmd, char	**envp)
{
	int		status;
	char	**path;

	status = get_path(&path, envp, *cmd);
	(void)envp;
	(void)cmd;
	return (status);
}

int	get_path(char ***path, char **envp, char *cmd)
{
	char	*str;

	str = NULL;
	while (*envp)
	{
		if (ft_strncmp("PATH=", *envp, 5) == 0)
		{
			str = *envp + 5;
			break ;
		}
		envp++;
	}
	if (!str)
		*path = ft_calloc(1, sizeof(char *));
	else
		*path = ft_split(str, COLON);
	if (!*path)
		return (MALLOC_ERR);
	return (0);
}
