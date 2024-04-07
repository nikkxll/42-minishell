/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   traverse_command_br.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnikifor <dnikifor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 13:37:47 by dshatilo          #+#    #+#             */
/*   Updated: 2024/04/07 23:25:53 by dnikifor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

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
