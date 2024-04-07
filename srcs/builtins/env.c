/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnikifor <dnikifor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 16:04:34 by dnikifor          #+#    #+#             */
/*   Updated: 2024/04/07 22:58:28 by dnikifor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

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
 * @param	ms pointer to the common project @c `t_minishell` structure
 * @return	@c `void`
 */
void	run_env(char **arr, t_minishell *ms)
{
	char	**new_env;
	int		len;

	len = ft_arrlen((void **)arr);
	new_env = ms->env;
	if (len > 0 && ft_strlen(arr[0]) > 1 && arr[0][0] == DASH)
	{
		arr[0][2] = NULL_TERM;
		print_arg_err_msg("env: `", arr[0], "': options are not supported\n");
		ms->exit_status = CMD_ARG_ERROR;
	}
	else if (len > 0)
	{
		print_arg_err_msg("env: `", arr[0], "': arguments are not supported\n");
		ms->exit_status = CMD_ARG_ERROR;
	}
	else
		print_env(new_env, -1);
}
