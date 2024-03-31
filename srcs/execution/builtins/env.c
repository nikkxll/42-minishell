/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnikifor <dnikifor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 16:04:34 by dnikifor          #+#    #+#             */
/*   Updated: 2024/04/01 01:41:29 by dnikifor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../headers/minishell.h"

/**
 * @brief	A function that writes environment list in stdout
 * @param	env an environment array
 * @param	j index
 * @return	@c `void`
 */
static void	print_env(char **env, int j)
{
	while (env[++j])
		ft_printf("%s\n", env[j]);
}

/**
 * @brief	A function that runs env built-in command
 * @param	arr array of arguments or options if allowed
 * @param	envp pointer to the environment array
 * @return	@c `SUCCESS`
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
		print_arg_err_msg("env: `", arr[0], "': options are not supported\n");
		return (SUCCESS);
	}
	else if (len >= 1)
	{
		print_arg_err_msg("env: `", arr[0], "': arguments are not supported\n");
		return (SUCCESS);
	}
	else
		print_env(new_env, -1);
	return (SUCCESS);
}
