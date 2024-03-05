/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnikifor <dnikifor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 11:21:06 by dnikifor          #+#    #+#             */
/*   Updated: 2024/03/05 22:57:57 by dnikifor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

int	run_pwd(char **arr)
{
	char	*working_dir;
	int		len;

	len = ft_arrlen((void **)arr);
	if (len > 1 && ft_strlen(arr[0]) > 1 && arr[0][0] == '-')
	{
		arr[0][2] = NULL_TERM;
		return (print_error_with_arg("invalid option\n", arr[0], "pwd: "));
	}
	working_dir = getcwd(NULL, 0);
	if (!working_dir)
	{
		perror("pwd");
		return (-1);
	}
	ft_printf("%s\n", working_dir);
	free(working_dir);
	return (1);
}
