/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnikifor <dnikifor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 15:22:52 by dnikifor          #+#    #+#             */
/*   Updated: 2024/03/28 13:52:03 by dnikifor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../headers/minishell.h"

/**
* @brief	A function that makes cd precheck for args amount
* @param	arr array of arguments or options if allowed
* @return	@c `-1` if input is not correct, @c `0` otherwise
*/
static int	cd_precheck(char **arr)
{
	int	len;

	len = ft_arrlen((void **)arr);
	if (len >= 1 && ft_strlen(arr[0]) > 1 && arr[0][0] == DASH)
	{
		if (arr[0][1] == DASH && arr[0][2] == NULL_TERM)
			return (0);
		arr[0][2] = NULL_TERM;
		print_arg_err_msg("cd: `", arr[0], "': options are not supported\n");
		return (-1);
	}
	if (len >= 2)
	{
		print_err_msg("cd: ", "too many arguments\n");
		return (-1);
	}
	return (0);
}

/**
* @brief	A function that updates @c `PWD` enviroment variable
* @param	envp pointer to the environment array
* @return	@c `MALLOC_ERR` if malloc failure occured, @c `SUCCESS` otherwise
*/
int	update_pwd(char ***envp)
{
	int		position;
	char	*cwd;

	position = env_var(*envp, "PWD=", -1, 4);
	if (position != -1)
	{
		cwd = getcwd(NULL, 0);
		if (!cwd)
			return (MALLOC_ERR);
		free((*envp)[position]);
		(*envp)[position] = ft_strjoin("PWD=", cwd);
		if (!(*envp)[position])
		{
			free(cwd);
			return (MALLOC_ERR);
		}
		free(cwd);
	}
	return (SUCCESS);
}

/**
* @brief	A function that runs cd built-in command
* @param	arr array of arguments or options if allowed
* @param	envp an environment array
* @return	@c `MALLOC_ERR` if malloc failure occured, @c `SUCCESS` otherwise
*/
int	run_cd(char **arr, char **envp)
{
	if (cd_precheck(arr) == -1)
		return (SUCCESS);
	if (arr[0][0] == NULL_TERM || !ft_strncmp(arr[0], "--", 2))
	{
		if (chdir(envp[env_var(envp, "HOME=", -1, 5)] + 5) != 0)
			print_arg_err_msg("cd: ", arr[0],
				": No such file or directory\n");
	}
	else if (!ft_strncmp(arr[0], "-", ft_strlen(arr[0])))
	{
		if (chdir(envp[env_var(envp, "OLDPWD=", -1, 7)] + 7) != 0)
			print_err_msg("cd: ", "OLDPWD not set\n");
		else
			ft_printf("%s\n", envp[env_var(envp, "OLDPWD=", -1, 7)] + 7);
	}
	else
	{
		if (chdir(arr[0]) != 0)
			print_arg_err_msg("cd: ", arr[0],
				": No such file or directory\n");
	}
	if (update_pwd(&envp) == MALLOC_ERR)
		return (MALLOC_ERR);
	return (SUCCESS);
}
