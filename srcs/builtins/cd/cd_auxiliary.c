/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_auxiliary.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnikifor <dnikifor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 19:20:23 by dnikifor          #+#    #+#             */
/*   Updated: 2024/04/10 19:58:33 by dnikifor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../headers/minishell.h"

/**
 * @brief	A function that makes updates pwd and oldpwd in the ms structure
 * @param	new_pwd new pwd string initialization
 * @param	ms pointer to the common project @c `t_minishell` structure
 * @return	@c `void`
 */
void	struct_pwd_and_full_oldpwd_update(char *new_pwd, t_minishell *ms)
{
	ms->oldpwd = ms->pwd;
	update_env_oldpwd(ms);
	if (ms->exit_status != SUCCESS)
		return ;
	new_pwd = getcwd(NULL, 0);
	if (!new_pwd)
	{
		print_err_msg("cd", ": getcwd error occured. "
			"Correct behavior is not guaranteed anymore\n");
		ms->exit_status = GETCWD_ERROR;
		return ;
	}
	ms->pwd = new_pwd;
}

/**
 * @brief	A function that makes cd precheck for args amount
 * @param	arr array of arguments or options if allowed
 * @param	ms pointer to the common project @c `t_minishell` structure
 * @return	@c `void`
 */
void	cd_precheck(char **arr, t_minishell *ms)
{
	int	len;

	len = ft_arrlen((void **)arr);
	if (len > 0 && ft_strlen(arr[0]) > 1 && arr[0][0] == DASH)
	{
		if (arr[0][1] == DASH && arr[0][2] == NULL_TERM)
			return ;
		arr[0][2] = NULL_TERM;
		print_arg_err_msg("cd: `", arr[0], "': options are not supported\n");
		ms->exit_status = CMD_ARG_ERROR;
	}
}

/**
 * @brief	A function that updates @c `PWD` enviroment variable
 * @param	ms pointer to the common project @c `t_minishell` structure
 * @param	position initialization for PWD position in env list (=0)
 * @param	cwd initialization for the cwd string
 * @param	temp initialization for the temp string
 * @return	@c `void`
 */
void	update_env_pwd(t_minishell *ms, int position, char *cwd, char *temp)
{
	position = env_var(ms->env, "PWD=", -1, 4);
	if (position != -1)
	{
		cwd = getcwd(NULL, 0);
		if (!cwd)
		{
			print_err_msg("cd", ": getcwd error occured. "
				"Correct behavior is not guaranteed anymore\n");
			ms->exit_status = GETCWD_ERROR;
			return ;
		}
		temp = ft_strjoin("PWD=", cwd);
		if (!temp)
		{
			print_err_msg("cd", ": malloc error occured. "
				"Correct behavior is not guaranteed anymore\n");
			free(cwd);
			ms->exit_status = MALLOC_ERR;
			return ;
		}
		free((ms->env)[position]);
		(ms->env)[position] = temp;
		free(cwd);
	}
}

/**
 * @brief	A function that initialize oldpwd when oldpwd does not 
 * exist
 * @param	i auxiliary index (equal to 0)
 * @param	ms pointer to the common project @c `t_minishell` structure
 * @return	@c `SUCCESS` if initialization succeed,
 * @c `MALLOC_ERR` if memory allocation fails
 */
static int	oldpwd_init_when_no_oldpwd_exists(int i, t_minishell *ms)
{
	int		len;
	char	**new_env;

	len = ft_arrlen((void **)(ms->env));
	if (add_to_env_list_new_env((ms->env), &new_env, &i, &len)
		== MALLOC_ERR)
		return (MALLOC_ERR);
	new_env[len] = ft_strjoin("OLDPWD=", ms->pwd);
	if (!new_env[len])
		return (MALLOC_ERR);
	ms->env = new_env;
	return (SUCCESS);
}

/**
 * @brief	A function that updates @c `PWD` enviroment variable
 * @param	ms pointer to the common project @c `t_minishell` structure
 * @return	@c `void`
 */
void	update_env_oldpwd(t_minishell *ms)
{
	int		position_pwd;
	int		position_oldpwd;
	char	*temp;

	position_oldpwd = env_var(ms->env, "OLDPWD=", -1, 7);
	position_pwd = env_var(ms->env, "PWD=", -1, 4);
	if (position_oldpwd != -1)
	{
		temp = ft_strjoin("OLDPWD=", ms->pwd);
		if (!temp)
		{
			ms->exit_status = MALLOC_ERR;
			return ;
		}
		free((ms->env)[position_oldpwd]);
		(ms->env)[position_oldpwd] = temp;
	}
	else if (position_oldpwd == -1 && position_pwd != -1
		&& ms->is_oldpwd_unset == false)
		ms->exit_status = oldpwd_init_when_no_oldpwd_exists(1, ms);
}
