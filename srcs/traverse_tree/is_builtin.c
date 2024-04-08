/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnikifor <dnikifor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 22:30:04 by dshatilo          #+#    #+#             */
/*   Updated: 2024/04/08 12:18:31 by dnikifor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

int	is_builtin(char *cmd)
{
	if (cmd == NULL)
		return (EMPTY_CMD);
	if (ft_strncmp(cmd, "echo", ECHO_LEN) == 0)
		return (ECHO);
	if (ft_strncmp(cmd, "cd", CD_LEN) == 0)
		return (CD);
	if (ft_strncmp(cmd, "pwd", PWD_LEN) == 0)
		return (PWD);
	if (ft_strncmp(cmd, "export", EXPORT_LEN) == 0)
		return (EXPORT);
	if (ft_strncmp(cmd, "unset", UNSET_LEN) == 0)
		return (UNSET);
	if (ft_strncmp(cmd, "env", ENV_LEN) == 0)
		return (ENV);
	if (ft_strncmp(cmd, "exit", EXIT_LEN) == 0)
		return (EXIT);
	return (NOT_BUILTIN);
}
