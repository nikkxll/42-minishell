/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shlvl_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnikifor <dnikifor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 00:39:31 by dnikifor          #+#    #+#             */
/*   Updated: 2024/04/01 01:40:46 by dnikifor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

/**
 * @brief	Auxiliary function that changes PWD in the enviroment list if it
 * exists
 * @param	position position of PWD in the enviroment list
 * @param	envp enviroment list
 * @return	@c `SUCCESS` if the operation completes successfully,
 * @c `MALLOC_ERR` if memory allocation fails during processing
 */
static int	shlvl_init_when_shlvl_exists(int position, char ***envp)
{
	int		number;
	char	*new_number;

	number = ft_atoi(ft_strrchr((*envp)[position], EQUAL) + 1);
	if (number <= 0)
		number = 0;
	new_number = ft_itoa(number);
	free((*envp)[position]);
	(*envp)[position] = ft_strjoin("SHLVL=", new_number);
	if (!(*envp)[position])
		return (MALLOC_ERR);
	return (SUCCESS);
}

/**
 * @brief	Auxiliary function that changes SHLVL in the enviroment list if it
 * does not exists
 * @param	envp enviroment list
 * @param	i number of entities to add (equal to 1)
 * @return	@c `SUCCESS` if the operation completes successfully,
 * @c `MALLOC_ERR` if memory allocation fails during processing
 */
static int	shlvl_init_when_no_shlvl_exists(char ***envp, int i)
{
	int		len;
	char	**new_env;

	len = ft_arrlen((void **)*envp);
	if (add_to_env_list_new_env_creation(*envp, &new_env, &i,
			&len) == MALLOC_ERR)
		return (MALLOC_ERR);
	new_env[len + i] = ft_strdup("SHLVL=1");
	if (!new_env[len + i])
	{
		ft_free_2d_array(new_env);
		perror("\033[0;31me-bash: \033[0;0m getcwd");
		return (MALLOC_ERR);
	}
	*envp = new_env;
	return (SUCCESS);
}

/**
 * @brief	Function that initialize SHLVL in the enviroment list
 * @param	envp enviroment list
 * @return	@c `status` of the execution
 */
int	shlvl_init(char ***envp)
{
	int		position;
	int		i;
	int		status;

	i = 1;
	status = 0;
	position = env_var(*envp, "SHLVL=", -1, 6);
	if (position == -1)
	{
		status = shlvl_init_when_no_shlvl_exists(envp, 1);
		if (status != 0)
			return (status);
	}
	else
	{
		status = shlvl_init_when_shlvl_exists(position, envp);
		if (status != 0)
			return (status);
	}
	return (status);
}
