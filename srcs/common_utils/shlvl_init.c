/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shlvl_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnikifor <dnikifor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 00:39:31 by dnikifor          #+#    #+#             */
/*   Updated: 2024/04/06 00:53:53 by dnikifor         ###   ########.fr       */
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
 * @param	number initialization for the shlvl env number (ft_atoi result)
 * @param	shlvl initialization for the shlvl env number (char passing into 
 * ft_atoi)
 * @return	@c `SUCCESS` if the operation completes successfully,
 * @c `MALLOC_ERR` if memory allocation fails during processing
 */
static int	shlvl_init_when_shlvl_exists(int position, char ***envp,
	int number, char *shlvl)
{
	char	*new_number;
	char	*temp;

	shlvl = ft_strrchr((*envp)[position], EQUAL) + 1;
	if (check_for_non_digits(shlvl))
		number = 0;
	else
		number = ft_atoi(shlvl);
	if (number < 0)
		number = -1;
	else if (number > 998)
	{
		shlvl_warning(number + 1);
		number = 0;
	}
	new_number = ft_itoa(number + 1);
	if (!new_number)
		return (MALLOC_ERR);
	temp = ft_strjoin("SHLVL=", new_number);
	free(new_number);
	if (!temp)
		return (MALLOC_ERR);
	free((*envp)[position]);
	(*envp)[position] = temp;
	return (SUCCESS);
}

/**
 * @brief	Auxiliary function that changes var in the enviroment list if it
 * does not exists
 * @param	envp enviroment list
 * @param	i auxiliary index (equal to 0)
 * @return	@c `SUCCESS` if the operation completes successfully,
 * @c `MALLOC_ERR` if memory allocation fails during processing
 */
int	var_init_when_no_var_exists(char ***envp, int i, char *var)
{
	int		len;
	char	**new_env;

	if (add_to_env_list_new_env(*envp, &new_env, &i,
			&len) == MALLOC_ERR)
		return (MALLOC_ERR);
	new_env[len] = ft_strdup(var);
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
		status = var_init_when_no_var_exists(envp, 1, "SHLVL=1");
		if (status != 0)
			return (status);
	}
	else
	{
		status = shlvl_init_when_shlvl_exists(position, envp, 0, NULL);
		if (status != 0)
			return (status);
	}
	return (status);
}
