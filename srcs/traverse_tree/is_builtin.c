/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnikifor <dnikifor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 22:30:04 by dshatilo          #+#    #+#             */
/*   Updated: 2024/04/10 18:55:04 by dnikifor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

/**
 * @brief	Check if a command is a built-in command
 * This function checks if the provided command is one of the built-in commands
 * @param	cmd The command to check
 * @return	Returns one of the following:
 * @return	- @c `C_EMPTY` if the command is empty
 * @return	- @c `C_ECHO` if the command is @c `echo`
 * @return	- @c `C_CD` if the command is @c `cd`
 * @return	- @c `C_PWD` if the command is @c `pwd`
 * @return	- @c `C_EXPORT` if the command is @c `export`
 * @return	- @c `C_UNSET` if the command is @c `unset`
 * @return	- @c `C_ENV` if the command is @c `env`
 * @return	- @c `C_EXIT` if the command is @c `exit`
 * @return	- @c `NOT_BUILTIN` if the command is not a built-in command
 */
int	is_builtin(char *cmd)
{
	if (cmd == NULL)
		return (C_EMPTY);
	if (ft_strncmp(cmd, "echo", ECHO_LEN) == 0)
		return (C_ECHO);
	if (ft_strncmp(cmd, "cd", CD_LEN) == 0)
		return (C_CD);
	if (ft_strncmp(cmd, "pwd", PWD_LEN) == 0)
		return (C_PWD);
	if (ft_strncmp(cmd, "export", EXPORT_LEN) == 0)
		return (C_EXPORT);
	if (ft_strncmp(cmd, "unset", UNSET_LEN) == 0)
		return (C_UNSET);
	if (ft_strncmp(cmd, "env", ENV_LEN) == 0)
		return (C_ENV);
	if (ft_strncmp(cmd, "exit", EXIT_LEN) == 0)
		return (C_EXIT);
	return (NOT_BUILTIN);
}
