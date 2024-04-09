/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dshatilo <dshatilo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 22:30:04 by dshatilo          #+#    #+#             */
/*   Updated: 2024/04/09 15:00:57 by dshatilo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

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
