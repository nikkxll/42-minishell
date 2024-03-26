/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors_print.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnikifor <dnikifor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 13:35:52 by dnikifor          #+#    #+#             */
/*   Updated: 2024/03/26 17:05:37 by dnikifor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../headers/minishell.h"

/**
* @brief	A function that prints an error with an argument in it
* @param	error error message
* @param	arg argument
* @param	cmd command
* @return	@c `void`
*/
void	print_error_with_arg(char *error, char *arg, char *cmd)
{
	ft_putstr_fd(cmd, 2);
	ft_putchar_fd('`', 2);
	ft_putstr_fd(arg, 2);
	ft_putstr_fd("': ", 2);
	ft_putstr_fd(error, 2);
}

/**
* @brief	A function that prints an error without any arguments in it
* @param	error error message
* @param	cmd command
* @return	@c `void`
*/
void	print_error(char *error, char *cmd)
{
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(error, 2);
}
