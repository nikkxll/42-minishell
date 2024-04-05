/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   traverse_command.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dshatilo <dshatilo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 15:17:19 by dshatilo          #+#    #+#             */
/*   Updated: 2024/04/05 10:50:57 by dshatilo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../headers/minishell.h"

int		execute_external(char **cmd, char *redir, t_minishell *ms);
int		execute_builtin(char **cmd, char *redir, t_minishell *ms);

int	traverse_command(char *cmd, char *redir, t_minishell *ms)
{
	int		status;
	char	**command;

	status = parse_cmd(cmd, &command, ms);
	if (status == 0)
	{
		if (is_builtin(command[0]) == true)
			status = execute_builtin(command, redir, ms);
		else
			status = execute_external(command, redir, ms);
	}
	ms->exit_status = status;
	ft_free_2d_array(command);
	return (status);
}

int	execute_external(char **command, char *redir, t_minishell *ms)
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
		waitpid(pid, &status, 0);
		if (WIFEXITED(status))
			return (WEXITSTATUS(status));
		return (EXIT_FAILURE);
	}
}

int	execute_builtin(char **command, char *redir, t_minishell *ms)
{
	// int	in_fd;
	// int	out_fd;
	int	status;

	// in_fd = dup(STDIN_FILENO);
	// out_fd = dup(STDOUT_FILENO);
	// if (in_fd == -1 || out_fd == -1)
	// {
	// 	if (in_fd != -1)
	// 		close(in_fd);
	// 	if (out_fd != -1)
	// 		close(out_fd);
	// 	print_err_msg(command[0], ": dup() error occured\n");
	// 	return (DUP_FAILURE);
	// }
	(void)redir; status = 0;//status = apply_redirect(redir);
	if (status == 0)
		status = command_run(command, ms);
	// if (dup2(in_fd, STDIN_FILENO) != -1 && dup2(out_fd, STDOUT_FILENO) != -1)
	// close fd after dup2()
	// 	print_err_msg(command[0], ": dup2() error occured. "
	// 		"Correct behavior is not guaranteed anymore\n");
	// 	return (DUP_P_FAILURE);
	// }
	return (status);
}
