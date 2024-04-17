/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepare_heredocs.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dshatilo <dshatilo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 16:23:59 by dshatilo          #+#    #+#             */
/*   Updated: 2024/04/17 18:22:13 by dshatilo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

static int	prepare_heredoc(char **limiter, char *hd_name);
static void	remove_spaces_and_quotes_hd(char *hd);
static int	heredoc(char *limiter, int fd);
static void	remove_hd_duplicates(char	***redirs, char *hd_name,
				char hd_counter);

int	prepare_heredocs(char ***redirs, char *hd_name, int	*hd_num)
{
	int		i;
	int		hd_counter;
	int		status;

	i = 0;
	hd_counter = 0;
	status = 0;
	while ((*redirs)[i] && status == 0)
	{
		if (ft_strncmp("<<", (*redirs)[i], 2) == 0)
		{
			hd_counter++;
			status = prepare_heredoc(*redirs + i, hd_name);
		}
		i++;
	}
	if (hd_counter > 0)
		(*hd_num)++;
	remove_hd_duplicates(redirs, hd_name, hd_counter);
	return (status);
}

static int	prepare_heredoc(char **limiter, char *hd_name)
{
	int		status;
	pid_t	pid;
	int		fd;

	remove_spaces_and_quotes_hd(*limiter + 2);
	pid = fork();
	if (pid == -1)
		return (FORK_FAILURE);
	if (pid == CHILD)
	{
		signal_interceptor(HEREDOC);
		toggler(IMPLICIT);
		fd = open(hd_name + 2, O_CREAT | O_WRONLY | O_TRUNC, 0644);
		if (fd != -1)
			heredoc(*limiter + 2, fd);
		exit(GENERIC_ERROR);
	}
	free(*limiter);
	*limiter = hd_name;
	status = wait_children(&pid, 1);
	return (status);
}

void	remove_spaces_and_quotes_hd(char *hd)
{
	int	i;

	while (ft_isspace(*hd))
	{
		i = 0;
		while (hd[i] != NULL_TERM)
		{
			hd[i] = hd[i + 1];
			i++;
		}
	}
	remove_quotes(hd, 0, 0);
}

static int	heredoc(char *limiter, int fd)
{
	char	*line;
	int		isequal;

	while (true)
	{
		line = readline("> ");
		if (!line)
		{
			close(fd);
			ft_printf("\033[1A");
			ft_printf("\033[2C");
			exit(0);
		}
		isequal = ft_strcmp(limiter, line);
		if (isequal != 0)
			ft_putendl_fd(line, fd);
		free(line);
		if (isequal == 0)
		{
			close(fd);
			exit(0);
		}
	}
}

void	remove_hd_duplicates(char	***redirs, char *hd_name, char hd_counter)
{
	int		i;
	int		j;
	char	**rdr;

	rdr = *redirs;
	i = 0;
	j = 0;
	if (hd_counter == 0)
		free(hd_name);
	while (hd_counter > 1)
	{
		if (rdr[i] == hd_name)
		{
			j = i;
			while (rdr[j] != NULL_TERM)
			{
				rdr[j] = rdr[j + 1];
				j++;
			}
			hd_counter--;
		}
		i++;
	}
}
