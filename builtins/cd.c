/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnikifor <dnikifor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 15:22:52 by dnikifor          #+#    #+#             */
/*   Updated: 2024/03/05 18:48:04 by dnikifor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

int	cd_precheck(char **arr, char **envp)
{
	int	len;

	len = ft_arrlen((void **)arr);
	if (len > 1 && ft_strlen(arr[1]) > 1 && arr[1][0] == '-')
	{
		arr[1][2] = NULL_TERM;
		return (print_error_with_arg("invalid option\n", arr[1], "cd: "));
	}
	if (len > 2)
		return (print_error("too many arguments\n", "cd: "));
	return (1);
}

static int	env_var(char **envp, char *var, int i, int j)
{
	while (envp[++i])
	{
		if (ft_strncmp(envp[i], var, j) == 0)
			break ;
	}
	return (i);
}

int	run_cd(char **arr, char **envp)
{
	if (cd_precheck(arr, envp) == -1)
		return (-1);
	if (arr[1][0] == NULL_TERM)
	{
		if (chdir(envp[env_var(envp, "HOME=", -1, 5)] + 5) != 0)
			return (print_error_with_arg("No such file or directory\n",
					arr[1], "cd: "));
	}
	else if (!ft_strncmp(arr[1], "-", ft_strlen(arr[1])))
	{
		if (chdir(envp[env_var(envp, "OLDPWD=", -1, 7)] + 7) != 0)
			return (print_error_with_arg("No such file or directory\n",
					arr[1], "cd: "));
		else
			printf("%s\n", envp[env_var(envp, "OLDPWD=", -1, 7)] + 7);
	}
	else
	{
		if (chdir(arr[1]) != 0)
			return (print_error_with_arg("No such file or directory\n",
					arr[1], "cd: "));
	}
	return (1);
}
