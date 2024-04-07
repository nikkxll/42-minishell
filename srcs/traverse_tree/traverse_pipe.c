/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   traverse_pipe.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnikifor <dnikifor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 17:43:12 by dshatilo          #+#    #+#             */
/*   Updated: 2024/04/07 23:25:59 by dnikifor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

int	traverse_first(t_node **node, t_minishell *ms, int pipefd[2], int pids[2]);
int	traverse_second(t_node **node, t_minishell *ms, int pipefd[2], int pids[2]);

int	traverse_pipe(t_node **root, t_minishell *ms)
{
	int		status;
	int		pipefd[2];
	pid_t	pids[2];
	t_node	*node;

	node = *root;
	if (pipe(pipefd) == -1)
		return (PIPE_FAILURE);
	status = traverse_first(&(node->left), ms, pipefd, pids);
	if (status == 0)
		status = traverse_second(&(node->right), ms, pipefd, pids);
	status = wait_children(pids, 2);
	return (status);
}

int	traverse_first(t_node **node, t_minishell *ms, int pipefd[2], int pids[2])
{
	int	status;

	pids[FIRST] = fork();
	if (pids[FIRST] == -1)
		return (FORK_FAILURE);
	if (pids[FIRST] == CHILD)
	{
		ms->is_parent = false;
		close(pipefd[READ]);
		if (dup2(pipefd[WRITE], STDOUT_FILENO) == -1)
		{
			close(pipefd[WRITE]);
			exit(DUP_FAILURE);
		}
		close(pipefd[WRITE]);
		status = traverse_tree(node, ms);
		exit(status);
	}
	else
		close(pipefd[WRITE]);
	return (0);
}

int	traverse_second(t_node **node, t_minishell *ms, int pipefd[2], int pids[2])
{
	int	status;

	pids[SECOND] = fork();
	if (pids[SECOND] == -1)
		return (FORK_FAILURE);
	if (pids[SECOND] == CHILD)
	{
		ms->is_parent = false;
		if (dup2(pipefd[READ], STDIN_FILENO) == -1)
		{
			close(pipefd[READ]);
			exit(DUP_FAILURE);
		}
		close(pipefd[READ]);
		status = traverse_tree(node, ms);
		exit(status);
	}
	else
		close(pipefd[READ]);
	return (0);
}
