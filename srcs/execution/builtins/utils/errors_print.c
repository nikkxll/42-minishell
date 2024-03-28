/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors_print.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnikifor <dnikifor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 13:35:52 by dnikifor          #+#    #+#             */
/*   Updated: 2024/03/28 13:58:37 by dnikifor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../headers/minishell.h"

/**
* @brief	A function that prints an error without any arguments in it
* @param	cmd command
* @param	msg error message
* @return	@c `void`
*/
void	print_err_msg(char *cmd, char *msg)
{
	cmd = ft_strjoin("\033[0;31me-bash: \033[0;0m", cmd);
	if (!cmd)
		return ;
	msg = ft_strjoin(cmd, msg);
	free(cmd);
	if (!msg)
		return ;
	ft_putstr_fd(msg, STDERR_FILENO);
	free(msg);
}

/**
* @brief	A function that prints an error with an argument in it
* @param	cmd command
* @param	arg argument
* @param	msg error message
* @return	@c `void`
*/
void	print_arg_err_msg(char *cmd, char *arg, char *msg)
{
	cmd = ft_strjoin("\033[0;31me-bash: \033[0;0m", cmd);
	if (!cmd)
		return ;
	arg = ft_strjoin(cmd, arg);
	free(cmd);
	if (!arg)
		return ;
	msg = ft_strjoin(arg, msg);
	free(arg);
	if (!msg)
		return ;
	ft_putstr_fd(msg, STDERR_FILENO);
	free(msg);
}
