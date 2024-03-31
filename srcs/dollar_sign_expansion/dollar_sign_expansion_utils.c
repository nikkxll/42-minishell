/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_sign_expansion_utils.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnikifor <dnikifor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 13:20:13 by dnikifor          #+#    #+#             */
/*   Updated: 2024/04/01 01:40:53 by dnikifor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

/**
 * @brief	Auxiliary function that searches for the variable inside @c `envp`
 * list
 * @param	envp environment array
 * @param	var string to search for
 * @param	i index
 * @param	j index
 * @return	@c `var` position in @c `envp` if exist, @c `NOT_FOUND` otherwise
 */
int	environment_search_exp_module(char **envp, char *var, int i, int j)
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

/**
 * @brief	Auxiliary function that changes the flag value if single or
 * double quote been found
 * @param	str iterated string
 * @param	i index
 * @param	single_q pointer to the single quote flag
 * @param	double_q pointer to the double quote flag
 * @return	@c `void`
 */
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
