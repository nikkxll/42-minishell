/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait_children.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dshatilo <dshatilo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 10:58:08 by dshatilo          #+#    #+#             */
/*   Updated: 2024/04/12 20:12:50 by dshatilo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

void	print_msg(int status);

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
	else if (WIFSIGNALED(status))
	{
		print_msg(status);
		return (status + 128);
	}
	return (EXIT_FAILURE);
}

void	print_msg(int status)
{
	int	sigcode;

	sigcode = WTERMSIG(status);
	if (sigcode == SIGINT)
		ft_putstr_fd("\n", STDERR_FILENO);
	else if (sigcode == SIGQUIT)
		ft_putstr_fd("Quit: 3\n", STDERR_FILENO);
	else if (sigcode == SIGABRT)
		ft_putstr_fd("Abort trap: 6\n", STDERR_FILENO);
	else if (sigcode == SIGKILL)
		ft_putstr_fd("Killed: 9\n", STDERR_FILENO);
	else if (sigcode == SIGBUS)
		ft_putstr_fd("Bus error: 10\n", STDERR_FILENO);
	else if (sigcode == SIGSEGV)
		ft_putstr_fd("Segmentation fault: 11\n", STDERR_FILENO);
	else
		;// ft_putstr_fd("Unknown signal\n", STDERR_FILENO);
}
