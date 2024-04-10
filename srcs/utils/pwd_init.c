/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dshatilo <dshatilo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 22:18:37 by dnikifor          #+#    #+#             */
/*   Updated: 2024/04/10 16:00:31 by dshatilo         ###   ########.fr       */
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
 * @c `GETCWD_ERROR` if an error occurs in getcwd() function
 */
static int	pwd_init_when_pwd_exists(int position, char ***envp, char **pwd)
{
	char	*temp;
	char	*cwd;

	cwd = getcwd(NULL, 0);
	if (!cwd)
	{
		perror("\033[0;31me-bash:\033[0;0m getcwd");
		return (GETCWD_ERROR);
	}
	*pwd = ft_strdup(cwd);
	if (!*pwd)
	{
		free(cwd);
		return (MALLOC_ERR);
	}
	temp = ft_strjoin("PWD=", cwd);
	free(cwd);
	if (!temp)
		return (MALLOC_ERR);
	free((*envp)[position]);
	(*envp)[position] = temp;
	return (SUCCESS);
}

/**
 * @brief	Auxiliary function that changes PWD in the enviroment list if it
 * does not exists
 * @param	cwd current working directory
 * @param	envp enviroment list
 * @param	i auxiliary index (equal to 0)
 * @param	pwd pointer to the pwd in minishell structure
 * @return	@c `SUCCESS` if the operation completes successfully,
 * @c `MALLOC_ERR` if memory allocation fails during processing,
 * @c `GETCWD_ERROR` if an error occurs in getcwd() function
 */
static int	pwd_init_when_no_pwd_exists(char ***envp, char **pwd)
{
	int		len;
	char	*cwd;
	char	**new_env;
	int		i;

	i = 1;
	if (add_to_env_list_new_env(*envp, &new_env, &i, &len) == MALLOC_ERR)
		return (MALLOC_ERR);
	cwd = getcwd(NULL, 0);
	if (!cwd)
	{
		perror("\033[0;31me-bash: \033[0;0m getcwd");
		return (GETCWD_ERROR);
	}
	*pwd = ft_strdup(cwd);
	if (*pwd)
		new_env[len] = ft_strjoin("PWD=", cwd);
	free(cwd);
	if (!pwd || !new_env[len])
		return (MALLOC_ERR);
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
	int		status;

	position = env_var(*envp, "PWD=", -1, 4);
	if (position == -1)
		status = pwd_init_when_no_pwd_exists(envp, pwd);
	else
		status = pwd_init_when_pwd_exists(position, envp, pwd);
	return (status);
}
