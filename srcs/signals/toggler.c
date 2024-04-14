/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   toggler.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnikifor <dnikifor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 01:02:26 by dnikifor          #+#    #+#             */
/*   Updated: 2024/04/15 01:02:48 by dnikifor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

/**
 * @brief	Toggle echoing of control characters in the terminal
 * @note	This function toggles the echoing of control characters in the
 * terminal. When the @c `mode` parameter is non-zero, it enables the echoing
 * of control characters. When @c `mode` is zero, it disables the echoing of
 * control characters.
 * @param	mode An integer indicating whether to enable (non-zero) or disable
 * (zero) the echoing of control characters
 * @return	@c `void`
 */
void	toggler(int mode)
{
	struct termios	terminal;

	tcgetattr(STDIN_FILENO, &terminal);
	if (mode)
		terminal.c_lflag |= ECHOCTL;
	else if (!mode)
		terminal.c_lflag &= ~ECHOCTL;
	tcsetattr(STDIN_FILENO, TCSANOW, &terminal);
}
