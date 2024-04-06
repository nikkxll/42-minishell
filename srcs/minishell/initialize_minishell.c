/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize_minishell.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dshatilo <dshatilo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 11:53:09 by dnikifor          #+#    #+#             */
/*   Updated: 2024/04/06 14:05:43 by dshatilo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

void	initialize_minishell(t_minishell **ms)
{
	extern char	**environ;
	int			status;

	status = 0;
	*ms = ft_calloc(1, sizeof(t_minishell));
	if (!*ms)
		status = MALLOC_ERR;
	if (status == 0)
	{
		(*ms)->env = cpy_env(environ);
		if (!(*ms)->env)
			status = MALLOC_ERR;
	}
	if (status == 0)
		status = pwd_init(&((*ms)->env), &((*ms)->pwd));
	if (status == 0)
		status = shlvl_init(&((*ms)->env));
	if (status != 0)
	{
		ft_free_minishell(*ms);
		ft_putstr_fd("\033[0;31me-bash:\033[0;0m can't initialize "
			"t_minishell structure\n", STDERR_FILENO);
		exit (status);
	}
	(*ms)->is_parent = true;
}
