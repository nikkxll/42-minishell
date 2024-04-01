/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnikifor <dnikifor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 15:11:23 by dnikifor          #+#    #+#             */
/*   Updated: 2024/04/02 00:39:57 by dnikifor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../headers/minishell.h"

//need to change later
void	run_exit(char **arr, t_minishell *ms)
{
	ft_putstr_fd("exit\n", 1);
	if (!*arr)
	{
		ms->exit_status = SUCCESS;
		exit(ms->exit_status);
	}
	ms->exit_status = ft_atoi(arr[0]);
	exit(ms->exit_status);
}
