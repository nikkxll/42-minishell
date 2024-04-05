/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnikifor <dnikifor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 20:08:13 by dnikifor          #+#    #+#             */
/*   Updated: 2024/04/03 20:08:33 by dnikifor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

/**
 * @brief	A function that allocates new array for the environment list
 * @param	envp an environment array
 * @return	new array
 */
char	**cpy_env(char **envp)
{
	char	**env;
	int		len;
	int		i;

	i = 0;
	len = ft_arrlen((void **)envp);
	env = ft_calloc(len + 1, sizeof(char *));
	if (!env)
		return (NULL);
	while (i < len)
	{
		env[i] = ft_strdup(envp[i]);
		if (!env[i])
		{
			ft_free_2d_array((void *)env);
			return (NULL);
		}
		i++;
	}
	return (env);
}
