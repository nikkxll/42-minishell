/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   traverse_pipe.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dshatilo <dshatilo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 17:43:12 by dshatilo          #+#    #+#             */
/*   Updated: 2024/03/29 15:20:56 by dshatilo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../headers/minishell.h"

int	traverse_first(t_node *node, char ***envp, int pipefd[2], int pids[2]);
int	traverse_second(t_node *node, char ***envp, int pipefd[2], int pids[2]);

int	traverse_pipe(t_node *node, char ***envp)
{
	int		status;
	int		pipefd[2];
	pid_t	pids[2];

	if (pipe(pipefd) == -1)
		return (PIPE_FAILURE);
	status = traverse_first(node->left, envp, pipefd, pids);
	if (status == 0)
		status = traverse_second(node->right, envp, pipefd, pids);
	status = wait_children(pids, 2);
	return (status);
}

int	traverse_first(t_node *node, char ***envp, int pipefd[2], int pids[2])
{

	pids[FIRST] = fork();
	if (pids[FIRST] == -1)
		return (FORK_FAILURE);
	if (pids[FIRST] == CHILD)
	{
		close(pipefd[READ]);
		if (dup2(pipefd[WRITE], STDOUT_FILENO) == -1)
		{
			close(pipefd[WRITE]);
			exit(DUP_FAILURE);
		}
		traverse_tree(node, envp);
		//Ensure that execution never reaches this line.
	}
	else
		close(pipefd[WRITE]);
	return (0);
}

int	traverse_second(t_node *node, char ***envp, int pipefd[2], int pids[2])
{
	pids[SECOND] = fork();
	if (pids[SECOND] == -1)
		return (FORK_FAILURE);
	if (pids[SECOND] == CHILD)
	{
		if (dup2(pipefd[READ], STDOUT_FILENO) == -1)
		{
			close(pipefd[READ]);
			exit(DUP_FAILURE);
		}
		traverse_tree(node, envp);
		//Ensure that execution never reaches this line.
	}
	else
		close(pipefd[READ]);
	return (0);
}
