/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepare_heredocs.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dshatilo <dshatilo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 16:23:59 by dshatilo          #+#    #+#             */
/*   Updated: 2024/08/23 12:42:56 by dshatilo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

static void	remove_spaces_and_quotes_hd(char *hd);
static void	heredoc(char *limiter, int fd, t_minishell *ms);
static void	handle_heredoc_line(int fd, char *line, t_minishell *ms,
				char *limiter);

/**
 * @brief	Prepare a here document for redirection
 * @note	This function prepares a here document for redirection. It removes
 * spaces and quotes from the limiter string, forks a child process to handle
 * the creation of the here document file, and waits for the child process to
 * complete. In the child process, it sets up signal handlers for heredoc mode,
 * toggles terminal echo for implicit newline, and creates the here document
 * file with the specified name. It then writes the content of the here document
 * until an EOF signal is received from the user.
 * @param	limiter The limiter string containing the delimiter for the here
 * document
 * @param	hd_name The name of the here document file
 * @param	ms A pointer to the minishell structure
 * @return	child exit code
 */
int	prepare_heredoc(char **limiter, char *hd_name, t_minishell *ms)
{
	int		status;
	pid_t	pid;
	int		fd;

	remove_spaces_and_quotes_hd(*limiter + 2);
	pid = fork();
	if (pid == -1)
		return (FORK_FAILURE);
	if (pid == CHILD)
	{
		signal_interceptor(HEREDOC);
		toggler(IMPLICIT);
		fd = open(hd_name + 2, O_CREAT | O_WRONLY | O_TRUNC, 0644);
		if (fd != -1)
			heredoc(*limiter + 2, fd, ms);
		exit(GENERIC_ERROR);
	}
	free(*limiter);
	*limiter = hd_name;
	status = wait_children(&pid, 1);
	return (status);
}

/**
 * @brief	Remove spaces and quotes from the here document limiter
 * @note	This function removes leading and trailing spaces from the
 * here document limiter string and removes any surrounding quotes. It
 * iterates through the string and shifts characters to the left until
 * all leading spaces are removed. Then, it removes any surrounding
 * quotes using the remove_quotes function.
 * @param	hd The here document limiter string
 * @return	@c `void`
 */
void	remove_spaces_and_quotes_hd(char *hd)
{
	int	i;

	while (ft_isspace(*hd))
	{
		i = 0;
		while (hd[i] != NULL_TERM)
		{
			hd[i] = hd[i + 1];
			i++;
		}
	}
	remove_quotes(hd, 0, 0);
}

/**
 * @brief	Handle the creation of a here document
 * @note	This function reads input lines from the user until the limiter
 * string is encountered. For each input line, it checks if the line is equal
 * to the limiter string. If not, it writes the line to the here document
 * file. If the limiter string is encountered, the function closes the here
 * document file and exits the process.
 * @param	limiter The limiter string indicating the end of the here document
 * @param	fd The file descriptor of the here document file
 * @param	ms A pointer to the minishell structure
 * @return	@c `void`
 */
static void	heredoc(char *limiter, int fd, t_minishell *ms)
{
	char	*line;
	int		isequal;

	while (true)
	{
		line = readline("> ");
		if (!line)
		{
			close(fd);
			ft_printf("\033[1A");
			ft_printf("\033[2C");
			exit(0);
		}
		isequal = ft_strcmp(limiter, line);
		if (isequal != 0)
			handle_heredoc_line(fd, line, ms, limiter);
		if (isequal == 0)
		{
			close(fd);
			exit(0);
		}
	}
}

/**
 * @brief	Removes duplicate entries of the here document filename from
 * an array of redirections
 * @note	This function iterates through the array of redirections and
 * removes any occurrence of the here document filename (hd_name) except
 * for one. The number of occurrences to be kept is determined by hd_counter.
 * @param	redirs A pointer to the array of redirections
 * @param	hd_name The here document filename to be removed
 * @param	hd_counter The number of occurrences of the here document
 * filename
 * @return	@c `void`
 */
void	remove_hd_duplicates(char ***redirs, char *hd_name, char hd_counter)
{
	int		i;
	int		j;
	char	**rdr;

	rdr = *redirs;
	i = 0;
	j = 0;
	if (hd_counter == 0)
		free(hd_name);
	while (hd_counter > 1)
	{
		if (rdr[i] == hd_name)
		{
			j = i;
			while (rdr[j] != NULL_TERM)
			{
				rdr[j] = rdr[j + 1];
				j++;
			}
			hd_counter--;
			continue ;
		}
		i++;
	}
}

/**
 * @brief	Handles each line of the heredoc input during the heredoc process
 * @note	This function performs dollar sign expansion on the input line,
 * writes the expanded line to the specified file descriptor (fd), and then
 * frees the allocated memory for the line. If a malloc error occurs during
 * dollar sign expansion, it prints an error message to stderr, closes the file
 * descriptor, and exits with the appropriate status.
 * @param	fd The file descriptor to write the line to
 * @param	line The input line to be handled
 * @param	ms The minishell structure containing environment variables
 * and exit status
 * @param	limiter The limiter string used to determine the end of the
 * heredoc input
 * @return	@c `void`
 */
static void	handle_heredoc_line(int fd, char *line, t_minishell *ms,
				char *limiter)
{
	int	status;

	status = dollar_sign_expansion(&line, ms->env, ms->exit_status);
	if (status == SUCCESS)
	{
		ft_putendl_fd(line, fd);
		free(line);
	}
	else
	{
		ft_putstr_fd("\033[0;31md-sh: \033[0;0m", STDERR_FILENO);
		ft_putstr_fd(limiter, STDERR_FILENO);
		ft_putendl_fd(": malloc() error occured", STDERR_FILENO);
		close(fd);
		exit(status);
	}
}
