/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnikifor <dnikifor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 11:21:06 by dnikifor          #+#    #+#             */
/*   Updated: 2024/03/28 13:53:47 by dnikifor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../headers/minishell.h"

/**
* @brief	A function that runs pwd built-in command
* @param	arr array of arguments or options if allowed
* @return	@c `MALLOC_ERR` if malloc failure occured, @c `SUCCESS` otherwise
*/
int	run_pwd(char **arr)
{
	char	*working_dir;
	int		len;

	len = ft_arrlen((void **)arr);
	if (len >= 1 && ft_strlen(arr[0]) > 1 && arr[0][0] == DASH)
	{
		arr[0][2] = NULL_TERM;
		print_arg_err_msg("pwd: `", arr[0], "': options are not supported\n");
		return (SUCCESS);
	}
	working_dir = getcwd(NULL, 0);
	if (!working_dir)
	{
		print_err_msg("pwd: ", "allocation error occured\n");
		return (MALLOC_ERR);
	}
	ft_printf("%s\n", working_dir);
	free(working_dir);
	return (SUCCESS);
}
