/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnikifor <dnikifor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 22:18:37 by dnikifor          #+#    #+#             */
/*   Updated: 2024/04/02 20:05:43 by dnikifor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

/**
 * @brief	Auxiliary function that changes PWD in the enviroment list if it
 * exists
 * @param	cdw current working directory
 * @param	position position of PWD in the enviroment list
 * @param	envp enviroment list
 * @return	@c `SUCCESS` if the operation completes successfully,
 * @c `MALLOC_ERR` if memory allocation fails during processing,
 * @c `SYSTEM_ERROR` if an error occurs in functions from imported libraries
 */
static int	pwd_init_when_pwd_exists(char cwd[PATH_MAX], int position,
	char ***envp, char **pwd)
{
	char	*temp;

	getcwd(cwd, PATH_MAX);
	if (!cwd)
	{
		perror("\033[0;31me-bash: \033[0;0m getcwd");
		return (SYSTEM_ERROR);
	}
	*pwd = ft_strdup(cwd);
	if (!*pwd)
		return (MALLOC_ERR);
	temp = ft_strjoin("PWD=", cwd);
	if (!temp)
	{
		free(*pwd);
		return (MALLOC_ERR);
	}
	free((*envp)[position]);
	(*envp)[position] = temp;
	return (SUCCESS);
}

/**
 * @brief	Auxiliary function that changes PWD in the enviroment list if it
 * does not exists
 * @param	cdw current working directory
 * @param	envp enviroment list
 * @param	i number of entities to add (equal to 1)
 * @return	@c `SUCCESS` if the operation completes successfully,
 * @c `MALLOC_ERR` if memory allocation fails during processing,
 * @c `SYSTEM_ERROR` if an error occurs in functions from imported libraries
 */
static int	pwd_init_when_no_pwd_exists(char cwd[PATH_MAX], char ***envp, int i,
	char **pwd)
{
	int		len;
	char	**new_env;

	len = ft_arrlen((void **)*envp);
	if (add_to_env_list_new_env_creation(*envp, &new_env, &i, &len)
		== MALLOC_ERR)
		return (MALLOC_ERR);
	getcwd(cwd, PATH_MAX);
	if (!cwd)
	{
		perror("\033[0;31me-bash: \033[0;0m getcwd");
		return (SYSTEM_ERROR);
	}
	*pwd = ft_strdup(cwd);
	if (!*pwd)
		return (MALLOC_ERR);
	new_env[len + i] = ft_strjoin("PWD=", cwd);
	if (!new_env[len + i])
	{
		free(*pwd);
		return (MALLOC_ERR);
	}
	*envp = new_env;
	return (SUCCESS);
}

/**
 * @brief	Function that initialize PWD in the enviroment list
 * @param	envp enviroment list
 * @return	@c `status` of the execution
 */
int	pwd_init(char ***envp, char **pwd)
{
	int		position;
	char	cwd[PATH_MAX];
	int		status;

	status = 0;
	position = env_var(*envp, "PWD=", -1, 4);
	if (position == -1)
	{
		status = pwd_init_when_no_pwd_exists(cwd, envp, 1, pwd);
		if (status != 0)
			return (status);
	}
	else
	{
		status = pwd_init_when_pwd_exists(cwd, position, envp, pwd);
		if (status != 0)
			return (status);
	}
	return (status);
}
