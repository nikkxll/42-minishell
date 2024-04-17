/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_ctrl_d.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dshatilo <dshatilo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 13:09:48 by dnikifor          #+#    #+#             */
/*   Updated: 2024/04/17 14:09:44 by dshatilo         ###   ########.fr       */
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
	int		len;
	char	*shift;
	char	*shift_len;

	len = ft_strlen(prompt);
	free(prompt);
	shift_len = ft_itoa(len);
	if (!shift_len)
		return (MALLOC_ERR);
	len = ft_strlen(shift_len) + 4;
	shift = ft_calloc(len, sizeof(char));
	if (!shift)
	{
		free(shift_len);
		return (MALLOC_ERR);
	}
	ft_strlcat(shift, "\033[", len);
	ft_strlcat(shift, shift_len, len);
	free(shift_len);
	ft_strlcat(shift, "C", len);
	ft_printf("\033[1A");
	ft_printf("%s", shift);
	free(shift);
	ft_printf("exit\n");
	return (SUCCESS);
}
