/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   locate_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dshatilo <dshatilo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 00:57:59 by dshatilo          #+#    #+#             */
/*   Updated: 2024/04/15 11:01:58 by dshatilo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

static int	get_path(char ***path, char **envp, char *command);

/**
 * @brief	Locate the command in the system
 * @note	This function locates the executable command in the system by
 * searching the directories specified in the PATH environment variable. It
 * first retrieves the PATH variable from the environment, then attempts to
 * find the executable command in each directory listed in the PATH. If the 
 * command is found, its path is updated accordingly
 * @param	command Pointer to the command to locate
 * @param	envp The array of environment variables
 * @return	Returns one of the following:
 * - @c `0` if the command is located successfully
 * - An error code indicating failure during the search process
 */
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

/**
 * @brief	Get the directories specified in the PATH environment variable
 * @note	This function retrieves the directories specified in the PATH
 * environment variable from the array of environment variables. It parses the
 * PATH variable to extract individual directory paths. If the PATH variable
 * is not found or empty, an empty array is allocated for the path. Memory
 * is allocated dynamically for the array of directory paths
 * @param	path Pointer to store the array of directory paths
 * @param	envp The array of environment variables
 * @param	command The command for which the PATH is being retrieved
 * @return	Returns one of the following:
 * - @c `0` if the PATH is retrieved successfully
 * - MALLOC_ERR if memory allocation fails
 */
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
