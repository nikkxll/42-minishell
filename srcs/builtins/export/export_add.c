/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_add.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnikifor <dnikifor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 17:35:13 by dnikifor          #+#    #+#             */
/*   Updated: 2024/04/07 22:57:58 by dnikifor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../headers/minishell.h"

/**
 * @brief	A function that allocates new array for addition
 * @param	envp environment array
 * @param	result pointer to the new environment array
 * @param	i pointer to the amount of entities to add
 * @param	len pointer to the environment list length
 * @return	@c `MALLOC_ERR` if malloc failure occured, @c `SUCCESS` otherwise
 */
int	add_to_env_list_new_env(char **envp, char ***result,
	int *i, int *len)
{
	*len = ft_arrlen((void **)envp);
	*result = (char **)ft_calloc(*len + *i + 1, sizeof(char *));
	if (!*result)
		return (MALLOC_ERR);
	ft_memcpy((void *)*result, (void *)envp, *len * sizeof(char *));
	free(envp);
	*i = 0;
	return (SUCCESS);
}

/**
 * @brief	A function that adds argument to the environment list
 * @param	new_env pointer to the new environment array
 * @param	arr array of arguments or options if allowed
 * @param	ms pointer to the common project @c `t_minishell` structure
 * @param	operations auxiliary array to calculate the number of operations
 * of different type
 * @return	@c `MALLOC_ERR` if malloc failure occured, @c `SUCCESS` otherwise
 */
int	add_to_env_list(char ***new_env, char **arr, t_minishell *ms,
	int *operations)
{
	int		i;
	int		j;
	int		len;
	char	*new_var;

	if (check_operations(operations, &i, &j, EXPORT_ADD))
		return (SUCCESS);
	if (add_to_env_list_new_env(ms->env, new_env, &i, &len) == MALLOC_ERR)
		return (MALLOC_ERR);
	while (operations[++j])
	{
		if (operations[j] == EXPORT_ADD)
		{
			if (ft_strncmp(arr[j], "OLDPWD=", 7) == 0)
				ms->is_oldpwd_unset = false;
			new_var = ft_strdup(arr[j]);
			if (new_var == NULL)
			{
				ft_free_2d_array(*new_env);
				return (MALLOC_ERR);
			}
			new_env[0][len + i++] = new_var;
		}
	}
	return (SUCCESS);
}
