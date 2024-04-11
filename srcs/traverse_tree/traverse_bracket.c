/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   traverse_bracket.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnikifor <dnikifor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 15:46:26 by dshatilo          #+#    #+#             */
/*   Updated: 2024/04/10 19:38:13 by dnikifor         ###   ########.fr       */
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

	pid = fork();
	if (pid == -1)
		return (FORK_FAILURE);
	if (pid == CHILD)
	{
		ms->is_parent = false;
		node = *root;
		status = traverse_tree(&(node->left), ms);
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
