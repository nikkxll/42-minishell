/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_minishell.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dshatilo <dshatilo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 14:01:52 by dshatilo          #+#    #+#             */
/*   Updated: 2024/04/06 14:03:03 by dshatilo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

void	ft_free_minishell(t_minishell *ms)
{
	if (!ms)
		return ;
	if (ms->env)
		ft_free_2d_array(ms->env);
	if (ms->pwd)
		free(ms->pwd);
	if (ms->oldpwd)
	{
		free(ms->oldpwd);
	}
	free(ms);
}
