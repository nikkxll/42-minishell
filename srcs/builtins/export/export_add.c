/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_add.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnikifor <dnikifor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 17:35:13 by dnikifor          #+#    #+#             */
/*   Updated: 2024/03/08 13:22:11 by dnikifor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../headers/minishell.h"

static int	add_to_env_list_new_env_creation(char **envp, char ***result,
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

int	add_to_env_list(char ***new_env, char **arr, char **envp,
	int *operations)
{
	int		i;
	int		j;
	int		len;
	char	*new_var;
	char	**result;

	result = *new_env;
	if (check_operations(operations, &i, &j, EXPORT_ADD))
		return (SUCCESS);
	if (add_to_env_list_new_env_creation(envp, &result, &i, &len) == MALLOC_ERR)
		return (MALLOC_ERR);
	while (operations[++j])
	{
		if (operations[j] == EXPORT_ADD)
		{
			new_var = ft_strdup(arr[j]);
			if (new_var == NULL)
			{
				ft_free_2d_array(result);
				return (MALLOC_ERR);
			}
			result[len + i++] = new_var;
		}
	}
	*new_env = result;
	return (SUCCESS);
}
