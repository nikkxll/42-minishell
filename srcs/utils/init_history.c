/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_history.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dshatilo <dshatilo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 11:02:33 by dshatilo          #+#    #+#             */
/*   Updated: 2024/04/11 12:47:53 by dshatilo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

void	read_history_file(t_minishell **ms);
void	add_ebash_history(char *cmd, t_minishell **minishell);

void	init_history(t_minishell **minishell)
{
	t_minishell	*ms;

	ms = *minishell;
	ms->history_path = ft_strjoin(ms->pwd, "/.e-bash_history");
	if (!ms->history_path)
	{
		print_err_msg("History file unsupported for current session", NULL);
		return ;
	}
	if (access(ms->history_path, F_OK) == 0)
		read_history_file(minishell);
}

void	read_history_file(t_minishell **ms)
{
	int			fd;
	int			status;
	char		*buffer;
	char		*curr;

	fd = open((*ms)->history_path, O_RDONLY);
	if (fd == -1)
	{
		perror_err_msg("History initialization error: ", (*ms)->history_path);
		return ;
	}
	buffer = NULL;
	curr = "";
	while (curr != NULL)
	{
		curr = get_next_line(fd, &status, &buffer);
		if (curr != NULL)
			add_ebash_history(curr, ms);
	}
	if (status != 0 && buffer != NULL)
		free(buffer);
	if (status != 0)
		ft_putstr_fd("\033[0;31me-bash:\033[0;0m GNL error occured while"
			" reading history file", STDERR_FILENO);
	close(fd);
}
