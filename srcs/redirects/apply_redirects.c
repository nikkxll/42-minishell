/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   apply_redirects.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnikifor <dnikifor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 22:24:56 by dshatilo          #+#    #+#             */
/*   Updated: 2024/04/08 20:15:48 by dnikifor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

int	apply_redirect(char *redir, t_minishell *ms, int *in, int *out);
int	replace_fd(int in, int out);

/**
 * @brief	Applies multiple redirection operations
 * @note	This function applies multiple redirection operations specified
 * in the @c `redir` string to the input and output streams of the minishell.
 * It splits the @c `redir` string into individual redirections, applies each
 * redirection using the @c `apply_redirect` function, and then replaces the
 * standard input and output file descriptors with the ones obtained from
 * the redirections. If any error occurs during the process, appropriate
 * error handling is performed, and the function returns a status code
 * indicating the failure.
 * @param	redir String containing multiple redirection specifications
 * @param	ms Pointer to the minishell structure @c `t_minishell`
 * @return	Integer status code indicating the success or failure of the
 * operation
 */
int	apply_redirects(char *redir, t_minishell *ms)
{
	char	**redirs;
	int		i;
	int		status;
	int		in;
	int		out;

	in = -1;
	out = -1;
	redirs = ft_split(redir, SEPARATOR);
	if (!redirs)
		return (MALLOC_ERR);
	status = 0;
	i = 0;
	while (redirs[i] && status == 0)
	{
		status = apply_redirect(redirs[i], ms, &in, &out);
		i++;
	}
	ft_free_2d_array(redirs);
	if (status == 0)
		status = replace_fd(in, out);
	return (status);
}

/**
 * @brief	Applies a single redirection operation
 * @note	This function applies a single redirection operation specified
 * by the @c `redir` string to the input and/or output streams of the
 * minishell. It checks the type of redirection (heredoc, append, input, or
 * output)and calls the corresponding function to perform the redirection.
 * If the operation is successful, it updates the file descriptors @c `in`
 * and/or @c `out` accordingly. If any error occurs during the process,
 * appropriate error handling is performed, and the function returns a status
 * code indicating the failure.
 * @param	redir String containing a single redirection specification
 * @param	ms Pointer to the minishell structure @c `t_minishell`
 * @param	in Pointer to the file descriptor of the current input stream
 * @param	out Pointer to the file descriptor of the current output stream
 * @return	Integer status code indicating the success or failure of the
 * operation
 */
int	apply_redirect(char *redir, t_minishell *ms, int *in, int *out)
{
	int	status;

	status = 0;
	if (ft_strncmp(redir, "<<", 2) == 0)
		status = apply_heredoc(redir + 2, in);
	else if (ft_strncmp(redir, ">>", 2) == 0)
		status = apply_append(redir + 2, ms, out);
	else if (ft_strncmp(redir, "<", 1) == 0)
		status = apply_redir_in(redir + 1, ms, in);
	else if (ft_strncmp(redir, ">", 1) == 0)
		status = apply_redir_out(redir + 1, ms, out);
	return (status);
}

/**
 * @brief	Replaces standard input and output file descriptors
 * @note	This function replaces the standard input file descriptor with the
 * specified input file descriptor @c `in` and the standard output file
 * descriptor with the specified output file descriptor @c `out`. It first
 * checks if the input file descriptor @c `in` is valid and, if so, duplicates
 * it to the standard input file descriptor @c `STDIN_FILENO`. Then, it checks
 * if the output file descriptor @c `out` is valid and, if so, duplicates it
 * to the standard output file descriptor @c `STDOUT_FILENO`. If any error
 * occurs during the process, appropriate error handling is performed,
 * and the function returns a status code indicating the failure.
 * @param	in File descriptor of the input stream to be replaced
 * @param	out File descriptor of the output stream to be replaced
 * @return	Integer status code indicating the success or failure of the
 * operation
 */
int	replace_fd(int in, int out)
{
	int	status;

	status = 0;
	if (in != -1)
	{
		if (dup2(in, STDIN_FILENO) == -1)
			status = DUP_FAILURE;
		close(in);
	}
	if (status == 0 && out != -1)
	{
		if (dup2(out, STDOUT_FILENO) == -1)
			status = DUP_FAILURE;
		close(out);
	}
	return (status);
}
