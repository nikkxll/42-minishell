/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnikifor <dnikifor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 15:11:23 by dnikifor          #+#    #+#             */
/*   Updated: 2024/04/03 00:45:15 by dnikifor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../headers/minishell.h"

long	ft_atol(const char *str)
{
	unsigned long	result;
	int				sign;

	result = 0;
	sign = 1;
	while ((*str >= 9 && *str <= 13) || *str == 32)
		str++;
	if ((*str == '-' || *str == '+') && ft_isdigit(*(str + 1)))
	{
		sign = -1 * (*str == '-') + 1 * (*str == '+');
		str++;
	}
	while (*str >= 48 && *str <= 57)
	{
		result = result * 10 + sign * (*str - 48);
		if ((sign == -1 && result > (unsigned long)0 - LONG_MIN) || result > LONG_MAX)
			return (0);
		str++;
	}
	return (result);
}

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
