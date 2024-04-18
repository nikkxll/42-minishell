/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepare_redirects.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnikifor <dnikifor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 13:32:25 by dshatilo          #+#    #+#             */
/*   Updated: 2024/04/19 00:28:39 by dnikifor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

static char	*get_hd_name(int *hd_num);
static int	prepare_heredocs(char ***redirs, int *hd_num, t_minishell *ms);
static void	remove_hd_files(int *hd_num);

/**
 * @brief	Prepares redirections based on the given redirects line, handling
 * any heredocs present
 * @param	redirects_line The line containing redirections to be parsed
 * @param	hd_num A pointer to an integer storing the number of heredoc
 * redirections
 * @param	redirs A pointer to a pointer to a character array, where
 * redirections will be stored
 * @param	ms Pointer to the minishell structure (`t_minishell`)
 * @return Returns @c `SUCCESS` if the redirections were prepared successfully,
 * @c `MALLOC_ERR` if there was a memory allocation error, or @c `SIGINT` + 128
 * if the process was interrupted by a @c `SIGINT` signal
 */
int	prepare_redirects(char *redirects_line, int *hd_num, char ***redirs,
		t_minishell *ms)
{
	int	status;

	if (redirects_line == NULL)
	{
		*redirs = NULL;
		return (SUCCESS);
	}
	*redirs = ft_split(redirects_line, SEPARATOR);
	free(redirects_line);
	if (!*redirs)
		return (MALLOC_ERR);
	status = prepare_heredocs(redirs, hd_num, ms);
	if (status != SUCCESS)
	{
		ft_free_2d_array(*redirs);
		remove_hd_files(hd_num);
	}
	if (status == SIGINT + 128)
		status = 1;
	return (status);
}

/**
 * @brief	Prepares heredoc redirections by handling each heredoc token
 * in the redirections array
 * @param	redirs A pointer to a pointer to a character array containing
 * redirection tokens
 * @param	hd_num A pointer to an integer storing the number of heredoc
 * redirections
 * @param	ms Pointer to the minishell structure (`t_minishell`)
 * @return	Returns @c `SUCCESS` if the heredocs were prepared successfully,
 * @c `MALLOC_ERR` if there was a memory allocation error, or the exit
 * status returned by prepare_heredoc if an error occurred during heredoc
 * preparation
 */
static int	prepare_heredocs(char ***redirs, int *hd_num, t_minishell *ms)
{
	int		i;
	int		hd_counter;
	int		status;
	char	*hd_name;

	hd_name = get_hd_name(hd_num);
	if (!hd_name)
		return (MALLOC_ERR);
	i = 0;
	hd_counter = 0;
	status = 0;
	while ((*redirs)[i] && status == 0)
	{
		if (ft_strncmp("<<", (*redirs)[i], 2) == 0)
		{
			hd_counter++;
			status = prepare_heredoc(*redirs + i, hd_name, ms);
		}
		i++;
	}
	if (hd_counter > 0)
		(*hd_num)++;
	remove_hd_duplicates(redirs, hd_name, hd_counter);
	return (status);
}

/**
 * @brief	Generates a unique filename for a heredoc based on the current
 * heredoc number
 * @param	hd_num A pointer to an integer storing the current number of
 * heredocs
 * @return	Returns a dynamically allocated string containing the generated
 * filename for the heredoc. Returns @c `NULL` if there was a memory
 * allocation error.
 */
static char	*get_hd_name(int *hd_num)
{
	char	*filename;
	char	*num;

	num = ft_itoa(*hd_num);
	if (!num)
		return (NULL);
	filename = ft_strjoin(HEREDOC_NAME, num);
	free(num);
	return (filename);
}

/**
 * @brief	Removes all heredoc files created during the shell session
 * @param	hd_num A pointer to an integer storing the number of heredocs
 * created during the session.
 * @return	@c `void`
 */
static void	remove_hd_files(int *hd_num)
{
	char	*file_name;
	char	*num;
	int		i;

	i = -1;
	while (++i < *hd_num)
	{
		num = ft_itoa(i);
		if (!num)
		{
			print_err_msg("unlink", ": malloc error occured");
			continue ;
		}
		file_name = ft_strjoin(&(HEREDOC_NAME[2]), num);
		free(num);
		if (!file_name)
		{
			print_err_msg("unlink", ": malloc error occured");
			continue ;
		}
		if (unlink(file_name) != 0)
			perror_err_msg("unlink: ", file_name);
		free(file_name);
	}
}
