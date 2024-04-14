/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   traverse_bracket.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnikifor <dnikifor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 15:46:26 by dshatilo          #+#    #+#             */
/*   Updated: 2024/04/15 00:12:00 by dnikifor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

/**
 * @brief	Traverse the subtree rooted at the current node in a separate
 * process
 * @note	This function forks a new process to traverse the subtree rooted
 * at the current node in the shell command tree. The child process is
 * responsible for traversing the subtree, while the parent process waits for
 * the child to complete. Once the traversal is finished, the status of the
 * child process is returned to the parent.
 * @param	root Pointer to the root of the tree
 * @param	ms Pointer to the minishell structure
 * @return	Returns the status of the traversal process
 */
int	traverse_bracket(t_node **root, t_minishell *ms)
{
	int		status;
	pid_t	pid;
	t_node	*node;

	if (ms->is_parent == false)
		signal_interceptor(DEFAULT);
	pid = fork();
	if (pid == -1)
		return (FORK_FAILURE);
	if (pid == CHILD)
	{
		signal_interceptor(DEFAULT);
		ms->is_parent = false;
		node = *root;
		status = traverse_tree(&(node->left), ms);
		exit (status);
	}
	else
		status = wait_children(&pid, 1);
	return (status);
}
