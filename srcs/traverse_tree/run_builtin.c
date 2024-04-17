/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_builtin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dshatilo <dshatilo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 15:49:24 by dshatilo          #+#    #+#             */
/*   Updated: 2024/04/17 17:39:32 by dshatilo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

int		run_builtin_without_redir(char **command, t_minishell *ms,
			int cmd_type);
int		run_builtin_with_redir(char **command, char **redir, t_minishell *ms,
			int cmd_type);
int		copy_std_fd(int *in_fd, int *out_fd, char *commmand);
void	return_std_fd(int	*in_fd, int *out_fd, int *status, char *command);

/**
 * @brief	Run the built-in command with or without redirection
 * @note	This function runs the built-in command specified by the command
 * array. If redirection is required, it calls the function to run the
 * built-in command with redirection; otherwise, it runs the built-in command
 * without redirection
 * @param	command The array of arguments representing the built-in command
 * @param	redir The redirection string, if redirection is required
 * @param	ms Pointer to the minishell structure
 * @param	cmd_type The type of built-in command
 * @return	Returns the status of running the built-in command
 */
int	run_builtin(char **command, char **redir, t_minishell *ms, int cmd_type)
{
	int	status;

	if (!redir)
		status = run_builtin_without_redir(command, ms, cmd_type);
	else
		status = run_builtin_with_redir(command, redir, ms, cmd_type);
	return (status);
}

/**
 * @brief	Run the built-in command without redirection.
 * @note	This function runs the built-in command specified by the command
 * array without redirection
 * @param	command The array of arguments representing the built-in command
 * @param	ms Pointer to the minishell structure
 * @param	cmd_type The type of built-in command
 * @return	Returns the status of running the built-in command
 */
int	run_builtin_without_redir(char **command, t_minishell *ms, int cmd_type)
{
	int	status;

	status = command_run(command, ms, cmd_type);
	return (status);
}

/**
 * @brief	Run the built-in command with redirection
 * @note	This function runs the built-in command specified by the command
 * array with redirection.
 * @param	command The array of arguments representing the built-in command
 * @param	redir The redirection string
 * @param	ms Pointer to the minishell structure
 * @param	cmd_type The type of built-in command
 * @return	Returns the status of running the built-in command with redirection
 */
int	run_builtin_with_redir(char **command, char **redir, t_minishell *ms,
	int cmd_type)
{
	int	status;
	int	in_fd;
	int	out_fd;

	status = copy_std_fd(&in_fd, &out_fd, command[0]);
	if (status == 0)
		status = apply_redirects(redir, ms);
	if (status == 0)
		status = command_run(command, ms, cmd_type);
	return_std_fd(&in_fd, &out_fd, &status, command[0]);
	return (status);
}

/**
 * @brief	Copy standard file descriptors for input and output
 * @note	This function duplicates the standard input and output file
 * descriptors @c `STDIN_FILENO` and @c `STDOUT_FILENO` and stores the
 * duplicated file descriptors in the provided pointers.
 * @param	in_fd Pointer to store the duplicated file descriptor for input
 * @param	out_fd Pointer to store the duplicated file descriptor for output
 * @param	command The name of the command for error messages
 * @return	Returns @c `0` if the file descriptors are duplicated successfully,
 * @c `DUP_FAILURE` if an error occurs during duplication
 */
int	copy_std_fd(int *in_fd, int *out_fd, char *command)
{
	*in_fd = dup(STDIN_FILENO);
	*out_fd = dup(STDOUT_FILENO);
	if (*in_fd == -1 || *out_fd == -1)
	{
		if (*in_fd != -1)
			close(*in_fd);
		if (*out_fd != -1)
			close(*out_fd);
		print_err_msg(command, ": dup() error occured\n");
		return (DUP_FAILURE);
	}
	return (0);
}

/**
 * @brief	Restore standard file descriptors for input and output
 * @note	This function restores the standard input and output file descriptors
 * @c `STDIN_FILENO` and @c `STDOUT_FILENO` to their original values using the
 * provided duplicated file descriptors. It also checks if there was any error
 * during the redirection process and updates the status accordingly.
 * @param	in_fd Pointer to the duplicated file descriptor for input
 * @param	out_fd Pointer to the duplicated file descriptor for output
 * @param	status Pointer to the status of the command execution
 * @param	command The name of the command for error messages
 * @return	@c `void`
 */
void	return_std_fd(int *in_fd, int *out_fd, int *status, char *command)
{
	int	redir_status;

	redir_status = 0;
	if (dup2(*in_fd, STDIN_FILENO) == -1 || dup2(*out_fd, STDOUT_FILENO) == -1)
	{
		print_err_msg(command, ": dup2() error occured. "
			"Correct behavior is not guaranteed anymore\n");
		redir_status = DUP_FAILURE;
	}
	close(*in_fd);
	close(*out_fd);
	if (*status == 0)
		*status = redir_status;
}
