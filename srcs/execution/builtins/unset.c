/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnikifor <dnikifor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 11:54:18 by dnikifor          #+#    #+#             */
/*   Updated: 2024/03/29 12:36:53 by dnikifor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../headers/minishell.h"

/**
* @brief	A function that searches for @c `var` in the @c `envp`
* @param	envp pointer to the environment array
* @param	var variable to search for
* @param	i index
* @return	@c `-1` if position not found, @c `position` (>= 0) otherwise
*/
static int	env_position_search(char ***envp, char *var, int i)
{
	char	**new_env;
	int		position;

	new_env = *envp;
	while (new_env[++i])
	{
		position = env_var(new_env, var, i - 1, ft_strlen(var));
		if (position == -1)
			return (-1);
		else if (new_env[position][ft_strlen(var)] == EQUAL)
			return (position);
		else
		{
			i += position;
			continue ;
		}
	}
	return (-1);
}

/**
* @brief	A function that unsetting argument from the environment list
* @param	envp pointer to the environment array
* @param	position position of an argument in the environment list
* @param	i index
* @return	@c `SUCCESS`
*/
static int	execute_unset(char ***envp, int position, int i)
{
	char	**new_env;

	new_env = *envp;
	if (new_env[i + 1] == NULL)
		return (SUCCESS);
	while (new_env[i + 1])
	{
		while (i < position)
			i++;
		if (i == position)
			free(new_env[i]);
		new_env[i] = new_env[i + 1];
		i++;
	}
	new_env[i] = NULL;
	*envp = new_env;
	return (SUCCESS);
}

/**
* @brief	A function that iterates through args and checks if they are
* in the environment list
* @param	arr array of arguments or options if allowed
* @param	envp pointer to the environment array
* @param	j pointer to the index
* @return	@c `void`
*/
static void	iterate_through_args(char **arr, char ***envp, int *j)
{
	int	position;
	int	i;

	i = 0;
	while (arr[*j][i] != NULL_TERM)
	{
		if (!ft_isenv(arr[*j][i], &i))
		{
			print_arg_err_msg("unset: `", arr[*j],
				"': not a valid identifier\n");
			return ;
		}
		i++;
	}
	if (arr[*j][0] == UNSCORE && arr[*j][1] == NULL_TERM)
		return ;
	position = env_position_search(envp, arr[*j], -1);
	if (position == -1)
		return ;
	else
		execute_unset(envp, position, 0);
	return ;
}

/**
* @brief	A function that runs unset built-in command
* @param	arr array of arguments or options if allowed
* @param	envp pointer to the environment array
* @return	@c `SUCCESS`
*/
int	run_unset(char **arr, char ***envp)
{
	int	len;
	int	j;

	j = -1;
	len = ft_arrlen((void **)arr);
	if (len >= 1 && ft_strlen(arr[0]) > 1 && arr[0][0] == DASH)
	{
		arr[0][2] = NULL_TERM;
		print_arg_err_msg("unset: `", arr[0], "': options are not supported\n");
		return (SUCCESS);
	}
	else if (len > 0)
	{
		while (arr[++j])
			iterate_through_args(arr, envp, &j);
	}
	return (SUCCESS);
}
