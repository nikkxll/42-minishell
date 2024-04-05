/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   apply_heredoc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dshatilo <dshatilo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 12:21:32 by dshatilo          #+#    #+#             */
/*   Updated: 2024/04/05 13:11:27 by dshatilo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

static int	heredoc(char *limiter, int fd);

int	apply_heredoc(char *limiter, int *in)
{
	int		status;
	int		hd[2];

	close(*in);
	while (*limiter == SPACE)
		limiter++;
	if (pipe(hd) == -1)
		return (PIPE_FAILURE);
	status = heredoc(limiter, hd[WRITE]);
	close(hd[WRITE]);
	if (status != 0)
		close(hd[READ]);
	else
		*in = hd[READ];
	return (status);
}

static int	heredoc(char *limiter, int fd)
{
	char	*line;
	int		iseuqal;

	ft_printf("YOU ARE HERE, limiter is :->%s<-", limiter);
	while (true)
	{
		line = readline("> ");
		if (!line)
			return (RL_FAILURE);
		iseuqal = ft_strcmp(limiter, line);
		if (iseuqal != 0)
			ft_putendl_fd(line, fd);
		free(line);
		if (iseuqal == 0)
			return (0);
	}
}
