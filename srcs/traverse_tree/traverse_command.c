/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   traverse_command.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnikifor <dnikifor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 15:17:19 by dshatilo          #+#    #+#             */
/*   Updated: 2024/04/10 19:36:40 by dnikifor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

int	run_external(char **cmd, char *redir, t_minishell *ms);

/**
 * @brief	Traverse a command node in the shell command tree
 * @note	This function traverses a command node in the shell command tree.
 * It first parses the command string into an array of arguments, then
 * determines if the command is a built-in command or an external command.
 * If it is a built-in command, it executes the command with or without
 * redirection as specified. If it is an external command, it executes the
 * command in a separate process with or without redirection as specified.
 * Finally, it updates the exit status in the minishell structure and frees the
 * memory allocated for the command array.
 * @param	cmd The command string to traverse
 * @param	redir The redirection string, if any
 * @param	ms Pointer to the minishell structure
 * @return	Returns the status of executing the command
 */
int	traverse_command(char *cmd, char *redir, t_minishell *ms)
{
	int		cmd_type;
	int		status;
	char	**command;

	status = parse_cmd(cmd, &command, ms);
	if (status == 0)
	{
		cmd_type = is_builtin(command[0]);
		if (cmd_type > 0)
			status = run_builtin(command, redir, ms, cmd_type);
		else
			status = run_external(command, redir, ms);
	}
	ms->exit_status = status;
	ft_free_2d_array(command);
	return (status);
}

/**
 * @brief	Execute an external command
 * @note	This function executes an external command specified by the command
 * array in a separate process. If redirection is specified, it applies the
 * redirection before executing the command. It then locates the command in the
 * system, and if found, executes it using the execve system call. If any error
 * occurs during the execution process, appropriate error messages are printed,
 * and the function exits with the corresponding error status.
 * @param	command The array of arguments representing the external command
 * @param	redir The redirection string, if any
 * @param	ms Pointer to the minishell structure
 * @return	Returns the status of executing the external command
 */
int	run_external(char **command, char *redir, t_minishell *ms)
{
	int		status;
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		return (FORK_FAILURE);
	if (pid == CHILD)
	{
		status = 0;
		if (redir != NULL)
			status = apply_redirects(redir, ms);
		if (status == 0)
			status = locate_command(&command[0], ms->env);
		if (status != 0)
			exit(status);
		execve(command[0], command, ms->env);
		print_err_msg(command[0], ": execve() error occured\n");
		exit(EXECVE_FAILURE);
	}
	else
	{
		status = wait_children(&pid, 1);
		return (status);
	}
}
