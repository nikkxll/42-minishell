/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepare_redirects.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dshatilo <dshatilo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 13:32:25 by dshatilo          #+#    #+#             */
/*   Updated: 2024/04/17 18:46:46 by dshatilo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

static char	*get_hd_name(int *hd_num);

int	prepare_redirects(char *redirects_line, int *hd_num, char ***redirs)
{
	char	*hd_name;
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
	hd_name = get_hd_name(hd_num);
	if (!hd_name)
	{
		ft_free_2d_array(*redirs);
		return (MALLOC_ERR);
	}
	status = prepare_heredocs(redirs, hd_name, hd_num);
	if (status == SIGINT + 128)
		status = 1;
	if (status != SUCCESS)
		ft_free_2d_array(*redirs);
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
