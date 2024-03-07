/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors_print.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnikifor <dnikifor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 13:35:52 by dnikifor          #+#    #+#             */
/*   Updated: 2024/03/07 19:50:29 by dnikifor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../headers/minishell.h"

void	print_error_with_arg(char *error, char *arg, char *cmd)
{
	if (*arg)
	{
		ft_putstr_fd(cmd, 2);
		ft_putchar_fd('`', 2);
		ft_putstr_fd(arg, 2);
		ft_putstr_fd("': ", 2);
		ft_putstr_fd(error, 2);
	}
	else
	{
		ft_putstr_fd(cmd, 2);
		ft_putstr_fd(": ", 2);
		ft_putstr_fd(error, 2);
	}
}

void	print_error(char *error, char *cmd)
{
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(error, 2);
}
