/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_builtin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dshatilo <dshatilo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 15:49:24 by dshatilo          #+#    #+#             */
/*   Updated: 2024/04/05 17:09:54 by dshatilo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../headers/minishell.h"

int		run_builtin_without_redir(char **command, t_minishell *ms);
int		run_builtin_with_redir(char **command, char *redir, t_minishell *ms);
int		copy_std_fd(int *in_fd, int *out_fd, char *commmand);
void	return_std_fd(int	*in_fd, int *out_fd, int *status, char *command);

int	run_builtin(char **command, char *redir, t_minishell *ms)
{
	int	status;

	if (!redir)
		status = run_builtin_without_redir(command, ms);
	else
		status = run_builtin_with_redir(command, redir, ms);
	return (status);
}

int	run_builtin_without_redir(char **command, t_minishell *ms)
{
	int	status;

	status = command_run(command, ms);
	return (status);
}

int	run_builtin_with_redir(char **command, char *redir, t_minishell *ms)
{
	int	status;
	int	in_fd;
	int	out_fd;

	status = copy_std_fd(&in_fd, &out_fd, command[0]);
	if (status == 0)
		status = apply_redirects(redir, ms);
	if (status == 0)
		status = command_run(command, ms);
	return_std_fd(&in_fd, &out_fd, &status, command[0]);
	return (status);
}

int	copy_std_fd(int *in_fd, int *out_fd, char *command)
{
	*in_fd = dup(STDIN_FILENO);
	*out_fd = dup(STDOUT_FILENO);
	if (*in_fd == -1 || *out_fd == -1)
	{
		if (*in_fd != -1)
			close(*in_fd);
		if (*out_fd != -1)
			close(*out_fd);
		print_err_msg(command, ": dup() error occured\n");
		return (DUP_FAILURE);
	}
	return (0);
}

void	return_std_fd(int	*in_fd, int *out_fd, int *status, char *command)
{
	int	redir_status;

	redir_status = 0;
	if (dup2(*in_fd, STDIN_FILENO) == -1 || dup2(*out_fd, STDOUT_FILENO) == -1)
	{
		print_err_msg(command, ": dup2() error occured. "
			"Correct behavior is not guaranteed anymore\n");
		redir_status = DUP_FAILURE;
	}
	close(*in_fd);
	close(*out_fd);
	if (*status == 0)
		*status = redir_status;
}
