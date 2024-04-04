/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shlvl_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnikifor <dnikifor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 00:39:31 by dnikifor          #+#    #+#             */
/*   Updated: 2024/04/04 17:41:02 by dnikifor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

/**
 * @brief	Auxiliary function that checks if string is in an appropriate
 * format
 * @param	str string to check
 * @return	@c `true` if the string is in a wrong format
 * @c `false` if the string is in a right format
 */
int	check_for_non_digits(char *str)
{
	while ((*str >= 9 && *str <= 13) || *str == 32)
		str++;
	if (*str == '+' || *str == '-')
		str++;
	while (*str >= '0' && *str <= '9')
		str++;
	while ((*str >= 9 && *str <= 13) || *str == 32)
		str++;
	if (*str != NULL_TERM)
		return (true);
	return (false);
}

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
	char	*temp;
	char	*shlvl;

	shlvl = ft_strrchr((*envp)[position], EQUAL) + 1;
	if (check_for_non_digits(shlvl))
		number = 0;
	else
		number = ft_atoi(shlvl);
	if (number < 0)
		number = -1;
	new_number = ft_itoa(number + 1);
	temp = ft_strjoin("SHLVL=", new_number);
	if (!temp)
		return (MALLOC_ERR);
	free((*envp)[position]);
	(*envp)[position] = temp;
	return (SUCCESS);
}

/**
 * @brief	Auxiliary function that changes SHLVL in the enviroment list if it
 * does not exists
 * @param	envp enviroment list
 * @param	i auxiliary index (equal to 0)
 * @return	@c `SUCCESS` if the operation completes successfully,
 * @c `MALLOC_ERR` if memory allocation fails during processing
 */
static int	shlvl_init_when_no_shlvl_exists(char ***envp, int i)
{
	int		len;
	char	**new_env;

	if (add_to_env_list_new_env(*envp, &new_env, &i,
			&len) == MALLOC_ERR)
		return (MALLOC_ERR);
	new_env[len] = ft_strdup("SHLVL=1");
	if (!new_env[len])
	{
		ft_free_2d_array(new_env);
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
	int		status;

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
