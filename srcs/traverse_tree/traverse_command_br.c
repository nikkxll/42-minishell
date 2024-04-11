/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   traverse_command_br.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnikifor <dnikifor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 13:37:47 by dshatilo          #+#    #+#             */
/*   Updated: 2024/04/10 19:38:07 by dnikifor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

/**
 * @brief	Traverse the subtree within the brackets with redirection
 * in a separate process
 * @note	This function forks a new process to traverse the subtree rooted at
 * the current node, which represents the brackets with redirection, in the
 * shell command tree. The child process is responsible for applying redirection
 * and traversing the right subtree, while the parent process waits for the
 * child to complete. Once the traversal is finished, the status of the child
 * process is returned to the parent.
 * @param	root Pointer to the root of the tree
 * @param	ms Pointer to the minishell structure
 * @return	Returns the status of the traversal process
 */
int	traverse_command_br(t_node **root, t_minishell *ms)
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
		status = apply_redirects(((t_redir *)(node->left))->str, ms);
		if (status == 0)
			status = traverse_tree(&(node->right), ms);
		exit (status);
	}
	else
	{
		waitpid(pid, &status, 0);
		if (WIFEXITED(status))
			return (WEXITSTATUS(status));
		return (EXIT_FAILURE);
	}
	return (0);
}
