/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   apply_redirect.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dshatilo <dshatilo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 22:24:56 by dshatilo          #+#    #+#             */
/*   Updated: 2024/04/03 23:20:07 by dshatilo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

int	apply_redirects(char *redir, t_minishell *ms)
{
	char	**redirs;
	int		i;
	int		status;

	(void)ms;
	redirs = ft_split(redir, SEPARATOR);
	if (!redirs)
		return (MALLOC_ERR);
	status = 0;
	i = 0;
	while (redirs[i] && status)
	{
		status = apply_redirect(redirs[i], ms);
		i++;
	}
	ft_free_2d_array(redirs);
	return (status);
}

int	apply_redirect(char *redir, t_minishell *ms)
{
	int	status;

	if (ft_strncmp(redir, "<<", 2) == 0)
		status = apply_heredoc(redir + 2);
	if (ft_strncmp(redir, ">>", 2) == 0)
		status = apply_apend(redir + 2);
	if (ft_strncmp(redir, "<", 1) == 0)
		status = apply_redir_in(redir + 2, ms);
	if (ft_strncmp(redir, ">", 1) == 0)
		status = apply_redir_out(redir + 2);
	return (status);
}
