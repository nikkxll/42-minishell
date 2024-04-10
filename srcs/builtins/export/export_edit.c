/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_edit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnikifor <dnikifor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 19:28:14 by dnikifor          #+#    #+#             */
/*   Updated: 2024/04/10 17:33:45 by dnikifor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../headers/minishell.h"

/**
 * @brief	A function that substitute new PWD string with previous version
 * @param	position position of PWD within env list
 * @param	str argument or option if allowed
 * @param	result the new environment array
 * @param	ms pointer to the common project @c `t_minishell` structure
 * @return	@c `MALLOC_ERR` if malloc failure occured, @c `SUCCESS` otherwise
 */
static int	edit_env_list_pwd(int position, char *str, char **result,
	t_minishell *ms)
{
	char	*new_var;

	free(ms->pwd);
	ms->pwd = ft_strdup(str + 4);
	if (!ms->pwd)
		return (MALLOC_ERR);
	new_var = ft_strdup(str);
	if (new_var == NULL)
	{
		if (ft_strncmp(result[position], "PWD=", 4) == 0)
			print_err_msg("PWD", ": malloc error occured. "
				"Correct behavior is not guaranteed anymore\n");
		return (MALLOC_ERR);
	}
	free(result[position]);
	result[position] = new_var;
	return (SUCCESS);
}

/**
 * @brief	A function that substitute new string with previous version
 * @param	str argument or option if allowed
 * @param	result the new environment array
 * @param	ms pointer to the common project @c `t_minishell` structure
 * @return	@c `MALLOC_ERR` if malloc failure occured, @c `SUCCESS` otherwise
 */
static int	edit_env_list_substitution(char *str, char **result,
	t_minishell *ms)
{
	int		position;
	char	*new_var;
	int		i;

	i = 0;
	while (str[i] != EQUAL)
		i++;
	position = env_var(result, str, -1, i);
	if (position == -1)
	{
		print_err_msg("EXPORT", ": add to env list error occured. "
			"Correct behavior is not guaranteed anymore\n");
		return (MALLOC_ERR);
	}
	if (ft_strncmp(result[position], "PWD=", 4) == 0)
		return (edit_env_list_pwd(position, str, result, ms));
	new_var = ft_strdup(str);
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
			if (edit_env_list_substitution(arr[j], result, ms) == MALLOC_ERR)
				return (MALLOC_ERR);
		}
	}
	return (SUCCESS);
}
