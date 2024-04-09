/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_edit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnikifor <dnikifor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 19:28:14 by dnikifor          #+#    #+#             */
/*   Updated: 2024/04/10 01:45:40 by dnikifor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../headers/minishell.h"

/**
 * @brief	A function that substitute edited string with previous version
 * @param	arr array of arguments or options if allowed
 * @param	result the new environment array
 * @param	j pointer to the index
 * @param	ms pointer to the common project @c `t_minishell` structure
 * @return	@c `MALLOC_ERR` if malloc failure occured, @c `SUCCESS` otherwise
 */
static int	edit_env_list_substitution(char **arr, char **result, int *j,
	t_minishell *ms)
{
	int		position;
	char	*new_var;
	int		i;

	i = 0;
	while (arr[*j][i] != EQUAL)
		i++;
	position = env_var(result, arr[*j], -1, i);
	if (ft_strncmp(result[position], "PWD=", 4) == 0)
	{
		free(ms->pwd);
		ms->pwd = ft_strdup(arr[*j] + 4);
		if (!ms->pwd)
			return (MALLOC_ERR);
	}
	new_var = ft_strdup(arr[*j]);
	if (new_var == NULL)
		return (MALLOC_ERR);
	free(result[position]);
	result[position] = new_var;
	return (SUCCESS);
}

/**
 * @brief	A function that edit an argument int the environment list
 * @param	new_env pointer to the new environment array
 * @param	arr array of arguments or options if allowed
 * @param	operations auxiliary array to calculate the number of operations
 * of different type
 * @param	ms pointer to the common project @c `t_minishell` structure
 * @return	@c `MALLOC_ERR` if malloc failure occured, @c `SUCCESS` otherwise
 */
int	edit_env_list(char ***new_env, char **arr, int *operations,
	t_minishell *ms)
{
	int		i;
	int		j;
	char	**result;

	result = *new_env;
	if (check_operations(operations, &i, &j, EXPORT_EDIT))
		return (SUCCESS);
	while (operations[++j])
	{
		if (operations[j] == EXPORT_EDIT)
		{
			if (edit_env_list_substitution(arr, result, &j, ms) == MALLOC_ERR)
				return (MALLOC_ERR);
		}
	}
	return (SUCCESS);
}
