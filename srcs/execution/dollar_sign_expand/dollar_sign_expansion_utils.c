/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_sign_expansion_utils.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnikifor <dnikifor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 13:20:13 by dnikifor          #+#    #+#             */
/*   Updated: 2024/03/22 13:29:52 by dnikifor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../headers/minishell.h"

int	enviroment_search_exp_module(char **envp, char *var, int i, int j)
{
	while (envp[++i])
	{
		if (ft_strncmp(envp[i], var, j) == 0)
		{
			if (envp[i][j] == EQUAL)
				return (i);
		}
	}
	return (NOT_FOUND);
}

void	index_quotes(char *str, int i, int *single_q, int *double_q)
{
	if (str[i] == S_QUOTE && !(*single_q) && !(*double_q))
		*single_q = 1;
	else if (str[i] == D_QUOTE && !(*double_q) && !(*single_q))
		*double_q = 1;
	else if (str[i] == S_QUOTE && !(*single_q) && *double_q == 1)
		*single_q = 2;
	else if (str[i] == D_QUOTE && !(*double_q) && *single_q == 1)
		*double_q = 2;
	else if (str[i] == S_QUOTE && *single_q)
		*single_q = 0;
	else if (str[i] == D_QUOTE && *double_q)
		*double_q = 0;
}
