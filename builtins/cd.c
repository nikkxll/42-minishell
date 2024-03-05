/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnikifor <dnikifor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 15:22:52 by dnikifor          #+#    #+#             */
/*   Updated: 2024/03/04 19:27:36 by dnikifor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

static int	home_path(char **envp, int i)
{
	while (envp[++i])
	{
		if (ft_strncmp(envp[i], "HOME=", 5) == 0)
			break ;
	}
	return (i);
}

int	run_cd(char **arr, char **envp)
{
	char	*home;

	home = envp[home_path(envp, -1)] + 5;
	if (arr[1][0] == NULL_TERM)
	{
		if (chdir(home) != 0)
		{
			perror("cd");
			return (-1);
		}
	}
	else
	{
		if (chdir(arr[1]) != 0)
		{
			perror("cd");
			return (-1);
		}
	}
	return (1);
}
