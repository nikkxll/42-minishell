/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnikifor <dnikifor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 11:54:18 by dnikifor          #+#    #+#             */
/*   Updated: 2024/03/07 19:51:25 by dnikifor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

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

static void	iterate_through_args(char **arr, char ***envp, int *j)
{
	int	position;

	if (arr[*j][0] == DASH)
	{
		print_error_with_arg("not a valid identifier\n", arr[*j],
			"unset: ");
		return ;
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

int	run_unset(char **arr, char ***envp)
{
	int	len;
	int	j;

	j = -1;
	len = ft_arrlen((void **)arr);
	if (len >= 1 && ft_strlen(arr[0]) > 1 && arr[0][0] == DASH)
	{
		arr[0][2] = NULL_TERM;
		print_error_with_arg("options not supported\n", arr[0], "unset: ");
		return (SUCCESS);
	}
	else if (len > 0)
	{
		while (arr[++j])
			iterate_through_args(arr, envp, &j);
	}
	return (SUCCESS);
}
