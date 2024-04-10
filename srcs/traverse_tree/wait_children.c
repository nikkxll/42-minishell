/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait_children.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnikifor <dnikifor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 10:58:08 by dshatilo          #+#    #+#             */
/*   Updated: 2024/04/10 19:55:39 by dnikifor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

/**
 * @brief	Wait for the termination of child processes
 * @note	This function waits for the termination of the specified number of
 * child processes with the given process IDs. It iterates over each process ID
 * and waits for the corresponding child process to terminate. After all child
 * processes have terminated, it returns the exit status of the last terminated
 * child process.
 * @param	pids Array of process IDs for the child processes
 * @param	num Number of child processes to wait for
 * @return	Returns the exit status of the last terminated child process
 */
int	wait_children(pid_t *pids, int num)
{
	int	i;
	int	status;

	i = 0;
	while (i < num)
	{
		if (pids[i] == -1)
			return (FORK_FAILURE);
		waitpid(pids[i], &status, 0);
		i++;
	}
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (EXIT_FAILURE);
}
