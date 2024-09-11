/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_ctrl_d.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnikifor <dnikifor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 13:09:48 by dnikifor          #+#    #+#             */
/*   Updated: 2024/09/07 10:57:29 by dnikifor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

/**
 * @brief	Handle errors related to Ctrl+D EOF
 * @note	This function prints an error message followed by an exit message
 * when Ctrl+D is pressed to indicate an end-of-file condition and error occured
 * when Ctrl+D handler fails
 * @param	msg The error message to be displayed
 * @return	@c `void`
 */
void	ctrl_d_error_handler(char *msg)
{
	ft_putstr_fd(msg, STDERR_FILENO);
	ft_putstr_fd("exit\n", STDERR_FILENO);
}

/**
 * @brief	Handle the Ctrl+D key combination
 * @note	This function handles the Ctrl+D key combination by printing the
 * exit message
 * @param	prompt The current prompt string
 * @return	@c `SUCCESS` upon successful handling of Ctrl+D
 */
int	handle_ctrl_d(char *prompt)
{
	free(prompt);
	ft_printf("exit\n");
	return (SUCCESS);
}
