/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnikifor <dnikifor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 15:22:52 by dnikifor          #+#    #+#             */
/*   Updated: 2024/03/08 23:17:46 by dnikifor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

static int	cd_precheck(char **arr)
{
	int	len;

	len = ft_arrlen((void **)arr);
	if (len >= 1 && ft_strlen(arr[0]) > 1 && arr[0][0] == DASH)
	{
		if (arr[0][1] == DASH && arr[0][2] == NULL_TERM)
			return (0);
		arr[0][2] = NULL_TERM;
		print_error_with_arg("options not supported\n", arr[0], "cd: ");
		return (-1);
	}
	if (len >= 2)
	{
		print_error("too many arguments\n", "cd: ");
		return (-1);
	}
	return (0);
}

int	run_cd(char **arr, char **envp)
{
	if (cd_precheck(arr) == -1)
		return (SUCCESS);
	if (arr[0][0] == NULL_TERM || !ft_strncmp(arr[0], "--", 2))
	{
		if (chdir(envp[env_var(envp, "HOME=", -1, 5)] + 5) != 0)
			print_error_with_arg("No such file or directory\n",
				arr[0], "cd: ");
	}
	else if (!ft_strncmp(arr[0], "-", ft_strlen(arr[0])))
	{
		if (chdir(envp[env_var(envp, "OLDPWD=", -1, 7)] + 7) != 0)
			print_error("OLDPWD not set\n", "cd: ");
		else
			ft_printf("%s\n", envp[env_var(envp, "OLDPWD=", -1, 7)] + 7);
	}
	else
	{
		if (chdir(arr[0]) != 0)
			print_error_with_arg("No such file or directory\n",
				arr[0], "cd: ");
	}
	return (SUCCESS);
}
