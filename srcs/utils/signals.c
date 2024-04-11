/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnikifor <dnikifor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 12:35:51 by dnikifor          #+#    #+#             */
/*   Updated: 2024/04/11 15:33:56 by dnikifor         ###   ########.fr       */
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

static void	sigint_catch(int sig)
{
	if (sig == SIGINT)
	{
		ioctl(0, TIOCSTI, "\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		ft_printf("\033[1A");
	}
}

void	catch_signal(int mode)
{
	if (mode == DEFAULT)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
	}
	else if (mode == INTERACTIVE)
	{
		signal(SIGINT, sigint_catch);
		signal(SIGQUIT, SIG_IGN);
	}
	else if (mode == HEREDOC)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_IGN);
	}
	else if (mode == IGNORE)
	{
		signal(SIGINT, SIG_IGN);
		signal(SIGQUIT, SIG_IGN);
	}
}
