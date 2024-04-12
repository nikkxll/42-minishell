/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dshatilo <dshatilo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 12:35:51 by dnikifor          #+#    #+#             */
/*   Updated: 2024/04/12 18:27:43 by dshatilo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

int	handle_ctrl_d(char *prompt)
{
	int		len;
	char	*shift;
	char	*shift_len;

	len = ft_strlen(prompt) - PROMPT_COLORS_LEN;
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
	ft_strlcat(shift, "C", len);
	ft_printf("\033[1A");
	ft_printf("%s", shift);
	ft_printf("exit\n");
	return (SUCCESS);
}

void	signal_chars_toggler(int toggle)
{
	struct termios	terminal;

	tcgetattr(STDIN_FILENO, &terminal);
	if (toggle)
		terminal.c_lflag |= ECHOCTL;
	else if (!toggle)
		terminal.c_lflag &= ~ECHOCTL;
	tcsetattr(STDIN_FILENO, TCSANOW, &terminal);
}

static void	sigint_im(int sig)
{
	if (sig == SIGINT)
	{
		ft_putstr_fd("\n", STDERR_FILENO);
		rl_on_new_line();
		rl_replace_line("", 1);
		rl_redisplay();
	}
}

void	signal_catcher(void (*first_handler)(int),
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

void	signal_mode_switch(int mode)
{
	if (mode == DEFAULT)
		signal_catcher(SIG_DFL, SIG_DFL);
	else if (mode == INTERACTIVE)
		signal_catcher(sigint_im, SIG_IGN);
	else if (mode == HEREDOC)
		signal_catcher(SIG_DFL, SIG_IGN);
	else if (mode == IGNORE)
		signal_catcher(SIG_IGN, SIG_IGN);
}
