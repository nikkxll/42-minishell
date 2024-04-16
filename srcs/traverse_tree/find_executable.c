/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_executable.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnikifor <dnikifor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 14:02:40 by dshatilo          #+#    #+#             */
/*   Updated: 2024/04/16 18:52:01 by dnikifor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

static int	check_path_provided(char *cmd_name, char **cmd_in_path);
static int	find_cmd_in_path(char *cmd_name, char **paths, char **cmd_in_path);
static char	*allocate_cmd_string(char *cmd_name, int *length, char **paths);
static int	check_cmd_in_path(char **candidate, int len,
				char *cmd_name, char *path);

/**
 * @brief	Find executable in specified paths
 * @note	Function searches for an executable command in the specified
 * paths. If the command includes a path, it directly checks whether the path
 * is valid. Otherwise, it searches the paths provided to find the executable.
 * If found, the command is updated with the full path of the executable
 * @param	command The command to find, possibly with a path
 * @param	paths An array of paths to search for the command
 * @return	Returns @c `0` if the executable is found and updated successfully,
 * @c `CMD_NF_FAILURE` if the command is not found,
 * @c `CMD_PD_FAILURE` if permission is denied,
 * @c `ISDIR_FAILURE` if the command is a directory
 */
int	find_executable(char **command, char **paths)
{
	int		status;
	char	*cmd_in_path;

	cmd_in_path = NULL;
	if (ft_strchr(command[0], '/') == NULL)
	{
		status = find_cmd_in_path(command[0], paths, &cmd_in_path);
		if (status == CMD_PD_FAILURE)
			print_err_msg(command[0], ": Permission denied\n");
	}
	else
		status = check_path_provided(command[0], &cmd_in_path);
	if (status == 0)
	{
		if (ft_strchr(command[0], '/') == NULL)
			free(command[0]);
		command[0] = cmd_in_path;
	}
	return (status);
}

/**
 * @brief	Check if the provided path to the command is valid
 * @note	Function checks if the provided path to the command
 * exists and is executable.
 * If the path is valid, it updates the pointer to the command in path.
 * @param	cmd_name The provided path to the command
 * @param	cmd_in_path Pointer to store the valid path to the command
 * @return	Returns @c `0` if the path is valid and executable,
 * @c `CMD_NF_FAILURE` if the command is not found,
 * @c `ISDIR_FAILURE` if the command is a directory,
 * @c `CMD_PD_FAILURE` if permission is denied
 */
static int	check_path_provided(char *cmd_name, char **cmd_in_path)
{
	struct stat	st;

	if (access(cmd_name, F_OK) != 0)
	{
		print_err_msg(cmd_name, ": No such file or directory\n");
		return (CMD_NF_FAILURE);
	}
	stat(cmd_name, &st);
	if (access(cmd_name, X_OK) != 0)
	{
		print_err_msg(cmd_name, ": Permission denied\n");
		return (CMD_PD_FAILURE);
	}
	if (S_ISDIR(st.st_mode))
	{
		print_err_msg(cmd_name, ": is a directory\n");
		return (CMD_PD_FAILURE);
	}
	*cmd_in_path = cmd_name;
	return (0);
}

/**
 * @brief	Find command in the specified paths
 * @note	This function searches for a command in the specified paths.
 * It constructs a full path by combining each path with the command name,
 * then checks if the constructed path is valid. If found, the valid path
 * to the command is stored in @c `cmd_in_path`
 * @param	cmd_name The name of the command to find
 * @param	paths An array of paths to search for the command
 * @param	cmd_in_path Pointer to store the valid path to the command
 * @return	Returns @c `0` if the command is found and its path is updated,
 * @c `MALLOC_ERR` if memory allocation fails,
 * @c `CMD_NF_FAILURE` if the command is not found,
 * @c `CMD_PD_FAILURE` if permission is denied
 */
static int	find_cmd_in_path(char *cmd_name, char **paths, char **cmd_in_path)
{
	int		status;
	char	*candidate;
	int		len;
	int		i;

	candidate = allocate_cmd_string(cmd_name, &len, paths);
	if (!candidate)
		return (MALLOC_ERR);
	i = 0;
	while (paths[i])
	{
		status = check_cmd_in_path(&candidate, len, cmd_name, paths[i]);
		if (status != 1)
		{
			if (status == 0)
				*cmd_in_path = candidate;
			else if (status == CMD_PD_FAILURE)
				free(candidate);
			return (status);
		}
		i++;
	}
	free(candidate);
	print_err_msg(cmd_name, ": command not found\n");
	return (CMD_NF_FAILURE);
}

/**
 * @brief	Allocate memory for constructing command strings
 * @note	Function allocates memory for constructing command strings
 * based on the provided command name and paths. It calculates the maximum
 * length required for the command string by considering the length of each
 * path and the command name. It then allocates memory accordingly and returns
 * a pointer to the allocated memory.
 * @param	cmd_name The name of the command
 * @param	len Pointer to an integer to store the length of the allocated memory
 * @param	paths Pointer to an array of strings representing the search paths
 * @return	Returns a pointer to the allocated memory for constructing command
 * strings
 */
static char	*allocate_cmd_string(char *cmd_name, int *len, char **paths)
{
	char	*cmd;
	int		curr_len;
	int		i;

	i = 0;
	*len = 0;
	while (paths[i])
	{
		curr_len = ft_strlen(paths[i]);
		if (curr_len > *len)
			*len = curr_len;
		i++;
	}
	*len += ft_strlen(cmd_name) + 1 + 1;
	cmd = (char *)ft_calloc(*len, sizeof(char));
	if (!cmd)
	{
		print_err_msg(cmd_name, ": allocation error occured\n");
		return (NULL);
	}
	return (cmd);
}

/**
 * @brief	Check if the command exists and is executable in the given path.
 * @note	This function checks if the command exists and is executable
 * in the specified path. It constructs the full path to the command by
 * concatenating the path with the command name and then checks if the
 * constructed path is valid.
 * @param	candidate Pointer to the constructed command path
 * @param	len Length of the constructed command path
 * @param	cmd_name The name of the command
 * @param	path The path to search for the command
 * @return	Returns @c `0` if the command exists and is executable,
 * @c `ISDIR_FAILURE` if the command is a directory,
 * @c `CMD_PD_FAILURE` if permission is denied,
 * @c `1` if the command does not exist
 */
static int	check_cmd_in_path(char **candidate, int len,
	char *cmd_name, char *path)
{
	char		*temp;
	struct stat	st;

	temp = *candidate;
	ft_memset(temp, 0, len);
	ft_strlcat(temp, path, len);
	ft_strlcat(temp, "/", len);
	ft_strlcat(temp, cmd_name, len);
	if (access(temp, F_OK) == 0)
	{
		stat(temp, &st);
		if (S_ISDIR(st.st_mode))
			return (1);
		if (access(temp, X_OK) == 0)
			return (0);
		else
			return (CMD_PD_FAILURE);
	}
	else
		return (1);
}
