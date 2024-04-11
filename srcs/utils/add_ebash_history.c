/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_ebash_history.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dshatilo <dshatilo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 11:08:31 by dshatilo          #+#    #+#             */
/*   Updated: 2024/04/11 12:57:58 by dshatilo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

void	print_err_history(char *cmd);

void	add_ebash_history(char *cmdline, t_minishell **minishell)
{
	t_minishell	*ms;
	t_list		*curr;
	char		*cmd;

	ms = *minishell;
	ft_remove_nl(cmdline);
	add_history(cmdline);
	if (ms->history_path == NULL)
		return ;
	cmd = ft_strdup(cmdline);
	if (!cmd)
	{
		print_err_history(cmdline);
		return ;
	}
	curr = ft_lstnew((void *)cmd);
	if (!curr)
	{
		free(cmd);
		print_err_history(cmdline);
		return ;
	}
	ft_lstadd_back(&(ms->history), curr);
	if (ft_lstsize(ms->history) > HIST_SIZE)
		ft_lstdel_front(&(ms->history), free);
}

void	print_err_history(char *cmd)
{
	ft_putstr_fd("\033[0;31me-bash: \033[0;0m", STDERR_FILENO);
	ft_putstr_fd(cmd, STDERR_FILENO);
	ft_putstr_fd(": can't add to history, ", STDERR_FILENO);
}
