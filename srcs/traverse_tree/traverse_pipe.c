/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   traverse_pipe.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dshatilo <dshatilo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 17:43:12 by dshatilo          #+#    #+#             */
/*   Updated: 2024/04/15 11:01:11 by dshatilo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

int	traverse_first(t_node **node, t_minishell *ms, int pipefd[2], int pids[2]);
int	traverse_second(t_node **node, t_minishell *ms, int pipefd[2], int pids[2]);

/**
 * @brief	Traverse a pipe node in the shell command tree
 * @note	This function traverses a pipe node in the shell command tree. It
 * creates a pipe to establish communication between the two commands connected
 * by the pipe. Then, it forks two child processes, one for each command. The
 * first child process executes the left command and writes its output to the
 * write end of the pipe. The second child process executes the right command,
 * reading its input from the read end of the pipe. After both child processes
 * have completed execution, the function waits for their termination and
 * returns the status of the second child process.
 * @param	root Pointer to the root of the tree
 * @param	ms Pointer to the minishell structure
 * @return	Returns the status of executing the second command in the pipe
 */
int	traverse_pipe(t_node **root, t_minishell *ms)
{
	int		status;
	int		pipefd[2];
	pid_t	pids[2];
	t_node	*node;

	if (ms->is_parent == false)
		signal_interceptor(DEFAULT);
	node = *root;
	if (pipe(pipefd) == -1)
		return (PIPE_FAILURE);
	status = traverse_first(&(node->left), ms, pipefd, pids);
	if (status == 0)
		status = traverse_second(&(node->right), ms, pipefd, pids);
	status = wait_children(pids, 2);
	return (status);
}

/**
 * @brief	Traverse the first command in a pipe
 * @note	This function traverses the left part of the pipe node,
 * representing the first command in the pipe. It forks a child process to
 * execute the command. The child process redirects its standard output to the
 * write end of the pipe and then executes the command. After the
 * execution, the child process exits with the status.
 * @param	node Pointer to the node representing the first command
 * @param	ms Pointer to the minishell structure
 * @param	pipefd Array containing file descriptors for the pipe
 * @param	pids Array containing process IDs for the child processes
 * @return	Returns the status of traversing the first command in the pipe
 */
int	traverse_first(t_node **node, t_minishell *ms, int pipefd[2], int pids[2])
{
	int	status;

	pids[FIRST] = fork();
	if (pids[FIRST] == -1)
		return (FORK_FAILURE);
	if (pids[FIRST] == CHILD)
	{
		signal_interceptor(DEFAULT);
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

/**
 * @brief	Traverse the second command in a pipe.
 * @note	This function traverses the right part of the pipe node, representing
 * the second command in the pipe. It forks a child process to execute the
 * command. The child process redirects its standard input to the read end of
 * the pipe and then executes the command. After the execution, the child process
 * exits with the status.
 * @param	node Pointer to the node representing the second command
 * @param	ms Pointer to the minishell structure
 * @param	pipefd Array containing file descriptors for the pipe
 * @param	pids Array containing process IDs for the child processes
 * @return	Returns the status of traversing the second command in the pipe
 */
int	traverse_second(t_node **node, t_minishell *ms, int pipefd[2], int pids[2])
{
	int	status;

	pids[SECOND] = fork();
	if (pids[SECOND] == -1)
		return (FORK_FAILURE);
	if (pids[SECOND] == CHILD)
	{
		signal_interceptor(DEFAULT);
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
