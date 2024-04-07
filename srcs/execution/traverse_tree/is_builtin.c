/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dshatilo <dshatilo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 22:30:04 by dshatilo          #+#    #+#             */
/*   Updated: 2024/04/07 05:41:31 by dshatilo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../headers/minishell.h"

t_bool	is_builtin(char *cmd)
{
	if (cmd == NULL)
		return (true);
	if (ft_strncmp(cmd, "echo", ECHO_LEN) == 0)
		return (true);
	if (ft_strncmp(cmd, "cd", CD_LEN) == 0)
		return (true);
	if (ft_strncmp(cmd, "pwd", PWD_LEN) == 0)
		return (true);
	if (ft_strncmp(cmd, "export", EXPORT_LEN) == 0)
		return (true);
	if (ft_strncmp(cmd, "unset", UNSET_LEN) == 0)
		return (true);
	if (ft_strncmp(cmd, "env", ENV_LEN) == 0)
		return (true);
	if (ft_strncmp(cmd, "exit", EXIT_LEN) == 0)
		return (true);
	return (false);
}
