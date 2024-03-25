/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnikifor <dnikifor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 16:04:34 by dnikifor          #+#    #+#             */
/*   Updated: 2024/03/25 23:24:55 by dnikifor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

/**
* @brief	A function that writes enviroment list in stdout
* @param	env an enviroment array
* @param	j index
* @return	`void`
*/
static void	print_env(char **env, int j)
{
	while (env[++j])
		ft_printf("%s\n", env[j]);
}

/**
* @brief	A function that runs env built-in command
* @param	arr array of arguments or options if allowed
* @param	envp pointer to the enviroment array
* @return	`SUCCESS`
*/
int	run_env(char **arr, char ***envp)
{
	char	**new_env;
	int		len;

	len = ft_arrlen((void **)arr);
	new_env = *envp;
	if (len >= 1 && ft_strlen(arr[0]) > 1 && arr[0][0] == DASH)
	{
		arr[0][2] = NULL_TERM;
		print_error_with_arg("options are not supported\n", arr[0], "env: ");
		return (SUCCESS);
	}
	else if (len >= 1)
	{
		print_error_with_arg("arguments not supported\n", arr[0], "env: ");
		return (SUCCESS);
	}
	else
		print_env(new_env, -1);
	return (SUCCESS);
}
