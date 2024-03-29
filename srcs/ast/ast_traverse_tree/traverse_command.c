/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   traverse_command.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dshatilo <dshatilo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 15:17:19 by dshatilo          #+#    #+#             */
/*   Updated: 2024/03/30 00:21:28 by dshatilo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../headers/minishell.h"

int		parse_cmd(char *cmd, char ***res, char **envp);
t_bool	is_builtin(char *cmd);
int		execute_external(char **cmd, char *redir, char **envp);
int		execute_builtin(char **cmd, char *redir, char **envp);

int	traverse_command(t_node *node, char ***envp)
{
	int			status;
	char		**cmd;

	status = (((t_command *)node)->cmd, &cmd, *envp);
	if (status == 0)
	{
		if (is_builtin(cmd[0]) == true)
			status = execute_builtin(cmd,
					((t_redir *)((t_command *)node)->redir)->str, envp);
		else
			status = execute_external(cmd,
					((t_redir *)((t_command *)node)->redir)->str, envp);
	}
	return (status);
}

t_bool	is_builtin(char *cmd)
{
	if (ft_strncmp(cmd, "echo", ECHO_LEN) == 0)
		return (true);
	if (ft_strncmp(cmd, "cd", CD_LEN) == 0)
		return (true);
	if (ft_strncmp(cmd, "pwd", PWD_LEN) == 0)
		return (true);
	if (ft_strncmp(cmd, "export", EXPORT_LEN) == 0)
		return (true);
	if (ft_strncmp(cmd, "unset", UNSET_LEN) == 0)
		return (true);
	if (ft_strncmp(cmd, "env", ENV_LEN) == 0)
		return (true);
	if (ft_strncmp(cmd, "exit", EXIT_LEN) == 0)
		return (true);
	return (false);
}

int	execute_external(char **cmd, char *redir, char **envp)
{
	// int		status;
	// pid_t	pid;

	// pid = fork();
	// if (pid == -1)
	// 	return (FORK_FAILURE);
	// if (pid == CHILD)
	// {
	// 	// apply_redirect(node->left);
	// 	traverse_tree(node->left, envp);
	// 	//Ensure that execution never reaches this line.
	// 	exit (0); // Remove it?
	// }
	// else
	// {
	// 	waitpid(pid, &status, 0);
	// 	if (WIFEXITED(status))
	// 		return (WEXITSTATUS(status));
	// 	return (EXIT_FAILURE);
	// }
	(void)node;
	(void)envp;
	return (0);
}

// void	execute_command(char *cmd, char **envp)
// {
// 	char	**cmd;
// 	int		child_status;

// 	child_status = get_command(px, i, &cmd);
// 	execve(cmd[0], cmd, px->envp);
// 	chld_execve_fail(px, cmd);
// }

int	execute_builtin(char **cmd, char *redir, char **envp)
{
	(void)node;
	(void)envp;
	return (0);
}
