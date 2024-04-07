/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   locate_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnikifor <dnikifor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 00:57:59 by dshatilo          #+#    #+#             */
/*   Updated: 2024/04/07 23:25:40 by dnikifor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

static int	get_path(char ***path, char **envp, char *command);

int	locate_command(char	**command, char	**envp)
{
	int		status;
	char	**path;

	status = get_path(&path, envp, *command);
	if (status != 0)
		return (status);
	status = find_executable(command, path);
	ft_free_2d_array(path);
	return (status);
}

static int	get_path(char ***path, char **envp, char *command)
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
	{
		print_err_msg(command, ": allocation error occured\n");
		return (MALLOC_ERR);
	}
	return (0);
}
