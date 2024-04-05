/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dshatilo <dshatilo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 22:18:37 by dnikifor          #+#    #+#             */
/*   Updated: 2024/04/05 18:30:53 by dshatilo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

/**
 * @brief	Auxiliary function that changes PWD in the enviroment list if it
 * exists
 * @param	cdw current working directory
 * @param	position position of PWD in the enviroment list
 * @param	envp enviroment list
 * @param	pwd pointer to the pwd in minishell structure
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
 * @param	i auxiliary index (equal to 0)
 * @param	pwd pointer to the pwd in minishell structure
 * @return	@c `SUCCESS` if the operation completes successfully,
 * @c `MALLOC_ERR` if memory allocation fails during processing,
 * @c `SYSTEM_ERROR` if an error occurs in functions from imported libraries
 */
static int	pwd_init_when_no_pwd_exists(char cwd[PATH_MAX], char ***envp, int i,
	char **pwd)
{
	int		len;
	char	**new_env;

	if (add_to_env_list_new_env(*envp, &new_env, &i, &len)
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
	new_env[len] = ft_strjoin("PWD=", cwd);
	if (!new_env[len])
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
 * @param	pwd pointer to the pwd in minishell structure
 * @return	@c `status` of the execution
 */
int	pwd_init(char ***envp, char **pwd)
{
	int		position;
	char	cwd[PATH_MAX];
	int		status;

	position = env_var(*envp, "PWD=", -1, 4);
	if (position == -1)
		status = pwd_init_when_no_pwd_exists(cwd, envp, 1, pwd);
	else
		status = pwd_init_when_pwd_exists(cwd, position, envp, pwd);
	return (status);
}
