/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   traverse_bracket.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dshatilo <dshatilo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 15:46:26 by dshatilo          #+#    #+#             */
/*   Updated: 2024/03/29 15:08:09 by dshatilo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../headers/minishell.h"

int	traverse_bracket(t_node *node, char ***envp)
{
	int		status;
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		return (FORK_FAILURE);
	if (pid == CHILD)
	{
		traverse_tree(node->left, envp);
		//Ensure that execution never reaches this line.
		exit (0); // Remove it?
	}
	else
	{
		waitpid(pid, &status, 0);
		if (WIFEXITED(status))
			return (WEXITSTATUS(status));
		return (EXIT_FAILURE);
	}
}
