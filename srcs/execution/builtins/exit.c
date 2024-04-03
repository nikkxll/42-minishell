/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnikifor <dnikifor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 15:11:23 by dnikifor          #+#    #+#             */
/*   Updated: 2024/04/03 16:01:18 by dnikifor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../headers/minishell.h"

void	run_exit(char **arr, t_minishell *ms)
{
	int	len;

	len = ft_arrlen((void **)arr);
	if (len >= 2)
	{
		ft_putstr_fd("exit\n", 1);
		print_err_msg("exit: ", "too many arguments\n");
		ms->exit_status = GENERIC_ERROR;
		//free all
		exit(ms->exit_status);
	}
	if (!*arr)
	{
		ft_putstr_fd("exit\n", 1);
		ms->exit_status = SUCCESS;
		//free all
		exit(ms->exit_status);
	}
	ms->exit_status = ft_atol(arr[0]);
	ft_putstr_fd("exit\n", 1);
	exit(ms->exit_status);
}
