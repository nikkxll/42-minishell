/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   traverse_command.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnikifor <dnikifor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 15:17:19 by dshatilo          #+#    #+#             */
/*   Updated: 2024/04/07 23:25:56 by dnikifor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

int		run_external(char **cmd, char *redir, t_minishell *ms);

int	traverse_command(char *cmd, char *redir, t_minishell *ms)
{
	int		status;
	char	**command;

	status = parse_cmd(cmd, &command, ms);
	if (status == 0)
	{
		if (is_builtin(command[0]) == true)
			status = run_builtin(command, redir, ms);
		else
			status = run_external(command, redir, ms);
	}
	ms->exit_status = status;
	ft_free_2d_array(command);
	return (status);
}

int	run_external(char **command, char *redir, t_minishell *ms)
{
	int		status;
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		return (FORK_FAILURE);
	if (pid == CHILD)
	{
		status = 0;
		if (redir != NULL)
			status = apply_redirects(redir, ms);
		if (status == 0)
			status = locate_command(&command[0], ms->env);
		if (status != 0)
			exit(status);
		execve(command[0], command, ms->env);
		print_err_msg(command[0], ": execve() error occured\n");
		exit(EXECVE_FAILURE);
	}
	else
	{
		status = wait_children(&pid, 1);
		return (status);
	}
}
