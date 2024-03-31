/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   traverse_command.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dshatilo <dshatilo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 15:17:19 by dshatilo          #+#    #+#             */
/*   Updated: 2024/04/01 02:05:12 by dshatilo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../headers/minishell.h"

int		execute_external(char **cmd, char *redir, char **envp);
int		execute_builtin(char **cmd, char *redir, char **envp);


int	traverse_command(char *cmd, char *redir, char ***envp)
{
	int		status;
	char	**command;

	status = parse_cmd(cmd, &command, *envp);
	if (status == 0)
	{
		if (is_builtin(cmd[0]) == true)
			status = execute_builtin(command, redir, envp);
		else
			status = execute_external(command, redir, envp);
	}
	return (status);
	return (0);
}

int	execute_external(char **command, char *redir, char **envp)
{
	int		status;
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		return (FORK_FAILURE);
	if (pid == CHILD)
	{
		//status = apply_redirect(node->left);
		if (status == 0)
			status = locate_command(&command[0], envp);
		if (status == 0)
			execve(command[0], command, envp);
		exit (status);
	}
	else
	{
		waitpid(pid, &status, 0);
		if (WIFEXITED(status))
			return (WEXITSTATUS(status));
		return (EXIT_FAILURE);
	}
}

int	execute_builtin(char **command, char *redir, char **envp)
{
	(void)command;
	(void)redir;
	(void)envp;
	return (0);
}
