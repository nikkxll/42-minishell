/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnikifor <dnikifor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 12:35:51 by dnikifor          #+#    #+#             */
/*   Updated: 2024/04/13 00:46:41 by dnikifor         ###   ########.fr       */
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

/**
 * @brief	Signal handler for interactive mode of SIGINT signal
 * @note	This function is called when a SIGINT signal is received in
 * interactive mode. It prints a newline character to standard error and
 * performs readline library cleanup to reset the input line.
 * @param	sig The signal number
 * @return	@c `void`
 */
static void	sigint_interactive(int sig)
{
	if (sig == SIGINT)
	{
		ioctl(0, TIOCSTI, "\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		ft_printf("\033[1A");
		g_sgnl = sig;
	}
}

/**
 * @brief	Initialize signal handlers for SIGINT and SIGQUIT
 * @note	This function initializes signal handlers for SIGINT and SIGQUIT
 * signals with the provided handler functions. It sets up signal actions for
 * the first and second handler functions specified.
 * @param	first_handler  Pointer to the function to handle the first signal
 * (@c `SIGINT`)
 * @param	second_handler Pointer to the function to handle the second signal
 * (@c `SIGQUIT`)
 * @return	@c `void`
 */
static void	interceptor_init(void (*first_handler)(int),
	void (*second_handler)(int))
{
	struct sigaction	sa;
	struct sigaction	sq;

	ft_memset(&sa, 0, sizeof(sa));
	ft_memset(&sq, 0, sizeof(sq));
	sa.sa_handler = first_handler;
	sq.sa_handler = second_handler;
	sigemptyset(&sa.sa_mask);
	sigemptyset(&sq.sa_mask);
	sa.sa_flags = SA_RESTART;
	sq.sa_flags = SA_RESTART;
	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGQUIT, &sq, NULL);
}

/**
 * @brief	Set signal handlers based on the mode
 * @note	This function sets signal handlers based on the mode provided.
 * Depending on the mode, different signal handlers are set for the SIGINT
 * signal. Modes:
 * @param	mode An integer representing the mode
 * @note	@c `DEFAULT` Set signal handlers to their default behavior
 * @note	@c `INTERACTIVE` Set signal handler for SIGINT to
 * @c `sigint_interactive()` and ignore SIGQUIT
 * @note	@c `HEREDOC` Set signal handler for SIGINT to its default behavior
 * and ignore SIGQUIT
 * @note	@c `IGNORE` Ignore both SIGINT and SIGQUIT signals
 * @return	@c `void`
 */
void	signal_interceptor(int mode)
{
	if (mode == DEFAULT)
		interceptor_init(SIG_DFL, SIG_DFL);
	else if (mode == INTERACTIVE)
		interceptor_init(sigint_interactive, SIG_IGN);
	else if (mode == HEREDOC)
		interceptor_init(SIG_DFL, SIG_IGN);
	else if (mode == IGNORE)
		interceptor_init(SIG_IGN, SIG_IGN);
}
