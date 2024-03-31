/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnikifor <dnikifor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 15:22:52 by dnikifor          #+#    #+#             */
/*   Updated: 2024/04/01 01:41:24 by dnikifor         ###   ########.fr       */
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
 * @brief	A function that handles change of directory to @c `OLDPWD`
 * @param	envp an environment array
 * @return	@c `void`
 */
static void	handle_cd_oldpwd(char **envp)
{
	int	env_variable;

	env_variable = env_var(envp, "OLDPWD=", -1, 7);
	if (env_variable == -1)
		print_err_msg("cd: ", "OLDPWD not set\n");
	else if (chdir(envp[env_variable] + 7) != 0)
		perror("\033[0;31me-bash: \033[0;0m cd");
	else
		ft_printf("%s\n", envp[env_variable] + 7);
}

/**
 * @brief	A function that handles change of directory to @c `HOME`
 * @param	envp an environment array
 * @return	@c `void`
 */
static void	handle_cd_home(char **envp)
{
	int	env_variable;

	env_variable = env_var(envp, "HOME=", -1, 5);
	if (env_variable == -1)
		print_err_msg("cd: ", "HOME not set\n");
	else if (chdir(envp[env_variable] + 5) != 0)
		perror("\033[0;31me-bash: \033[0;0m cd");
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
	if (ft_arrlen((void **)arr) == 0 || !ft_strncmp(arr[0], "--", 2))
		handle_cd_home(envp);
	else if (!ft_strncmp(arr[0], "-", ft_strlen(arr[0]))
		&& ft_strlen(arr[0]) > 0)
		handle_cd_oldpwd(envp);
	else if (ft_strlen(arr[0]) == 0)
	{
		if (chdir(".") != 0)
			perror("\033[0;31me-bash: \033[0;0m cd");
	}
	else
	{
		if (chdir(arr[0]) != 0)
			perror("\033[0;31me-bash: \033[0;0m cd");
	}
	if (update_pwd(&envp) == MALLOC_ERR)
		return (MALLOC_ERR);
	return (SUCCESS);
}
