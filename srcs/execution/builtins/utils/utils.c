/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnikifor <dnikifor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 12:00:54 by dnikifor          #+#    #+#             */
/*   Updated: 2024/04/01 01:41:19 by dnikifor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../headers/minishell.h"

/**
 * @brief	Skips all @c `symbol` characters in a string
 * @param	str string to skip chars in
 * @param	i pointer to the index
 * @param	symbol character
 * @return	@c `void`
 */
void	skip_characters(char *str, int *i, int symbol)
{
	while (str[*i] == symbol && str[*i] != NULL_TERM)
		(*i)++;
}

/**
 * @brief	A function that checks if @c `var` included in the environment
 * list
 * @param	envp an environment array
 * @param	var search string
 * @param	i an index
 * @param	j an index
 * @return	@c `i` if var was found, @c `NOT_FOUND` otherwise
 */
int	env_var(char **envp, char *var, int i, int j)
{
	while (envp[++i])
	{
		if (ft_strncmp(envp[i], var, j) == 0)
			return (i);
	}
	return (NOT_FOUND);
}

/**
 * @brief	A function that checks if @c `var` included in the @c `arr`
 * @param	arr array of arguments
 * @param	var search string
 * @param	i an index
 * @param	j an index
 * @return	@c `i` if var was found, @c `NOT_FOUND` otherwise
 */
int	arg_var(char **arr, char *var, int i, int j)
{
	while (--i >= 0)
	{
		if (ft_strncmp(arr[i], var, j) == 0)
			return (i);
	}
	return (NOT_FOUND);
}
