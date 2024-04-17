/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepare_redirects.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dshatilo <dshatilo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 13:32:25 by dshatilo          #+#    #+#             */
/*   Updated: 2024/04/17 20:30:52 by dshatilo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

static char	*get_hd_name(int *hd_num);
static int	prepare_heredocs(char ***redirs, int *hd_num);
static void	remove_hd_files(int *hd_num);

int	prepare_redirects(char *redirects_line, int *hd_num, char ***redirs)
{
	int		status;

	if (redirects_line == NULL)
	{
		*redirs = NULL;
		return (SUCCESS);
	}
	*redirs = ft_split(redirects_line, SEPARATOR);
	free(redirects_line);
	if (!*redirs)
		return (MALLOC_ERR);
	status = prepare_heredocs(redirs, hd_num);
	if (status != SUCCESS)
	{
		ft_free_2d_array(*redirs);
		remove_hd_files(hd_num);
	}
	if (status == SIGINT + 128)
		status = 1;
	return (status);
}

static int	prepare_heredocs(char ***redirs, int *hd_num)
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
			status = prepare_heredoc(*redirs + i, hd_name);
		}
		i++;
	}
	if (hd_counter > 0)
		(*hd_num)++;
	remove_hd_duplicates(redirs, hd_name, hd_counter);
	return (status);
}

static char	*get_hd_name(int *hd_num)
{
	char	*filename;
	char	*num;

	num = ft_itoa(*hd_num);
	if (!num)
		return (NULL);
	filename = ft_strjoin("<<.heredoc_", num);
	free(num);
	return (filename);
}

static void	remove_hd_files(int *hd_num)
{
	(void)hd_num;
}
