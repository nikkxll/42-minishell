/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnikifor <dnikifor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 11:21:06 by dnikifor          #+#    #+#             */
/*   Updated: 2024/04/07 22:58:34 by dnikifor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

/**
 * @brief	A function that runs pwd built-in command
 * @param	arr array of arguments or options if allowed
 * @param	ms pointer to the common project @c `t_minishell` structure
 * @return	@c `void`
 */
void	run_pwd(char **arr, t_minishell *ms)
{
	char	*working_dir;
	int		len;

	len = ft_arrlen((void **)arr);
	if (len > 0 && ft_strlen(arr[0]) > 1 && arr[0][0] == DASH)
	{
		arr[0][2] = NULL_TERM;
		print_arg_err_msg("pwd: `", arr[0], "': options are not supported\n");
		ms->exit_status = CMD_ARG_ERROR;
		return ;
	}
	working_dir = getcwd(NULL, 0);
	if (!working_dir)
	{
		ms->exit_status = GETCWD_ERROR;
		return ;
	}
	ft_printf("%s\n", working_dir);
	free(working_dir);
}
