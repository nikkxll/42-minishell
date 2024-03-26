/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnikifor <dnikifor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 11:21:06 by dnikifor          #+#    #+#             */
/*   Updated: 2024/03/26 17:05:16 by dnikifor         ###   ########.fr       */
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
		print_error_with_arg("options are not supported\n", arr[0], "pwd: ");
		return (SUCCESS);
	}
	working_dir = getcwd(NULL, 0);
	if (!working_dir)
	{
		print_error("allocation error occured\n", "pwd: ");
		return (MALLOC_ERR);
	}
	ft_printf("%s\n", working_dir);
	free(working_dir);
	return (SUCCESS);
}
