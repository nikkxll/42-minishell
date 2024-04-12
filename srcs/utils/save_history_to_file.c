/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_history_to_file.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dshatilo <dshatilo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 12:16:21 by dshatilo          #+#    #+#             */
/*   Updated: 2024/04/11 13:24:14 by dshatilo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

void	write_lst(void *str);

void	save_history_to_file(t_minishell *ms)
{
	int	fd;

	if (ms->history_path == NULL)
		return ;
	if (access(ms->history_path, F_OK) != 0)
		ft_printf("Creating history file :%s\n", ms->history_path);
	fd = open(ms->history_path, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd == -1 || dup2(fd, STDOUT_FILENO) == -1)
	{
		close(fd);
		perror_err_msg("Can't write to history file: ", ms->history_path);
		return ;
	}
	close(fd);
	ft_lstiter(ms->history, write_lst);
}

void	write_lst(void *str)
{
	ft_printf("%s\n", str);
}
