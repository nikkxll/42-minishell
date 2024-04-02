/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnikifor <dnikifor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 19:20:23 by dnikifor          #+#    #+#             */
/*   Updated: 2024/04/02 19:51:58 by dnikifor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../headers/minishell.h"

/**
 * @brief	A function that makes updates pwd and oldpwd in the ms structure
 * @param	new_pwd new pwd string initialization
 * @param	ms pointer to the common project @c `t_minishell` structure
 * @return	@c `void`
 */
void	struct_pwd_oldpwd_update(char *new_pwd, t_minishell *ms)
{
	ms->oldpwd = ms->pwd;
	new_pwd = getcwd(NULL, 0);
	if (!new_pwd)
	{
		ms->exit_status = GETCWD_ERROR;
		return ;
	}
	ms->pwd = new_pwd;
}

/**
 * @brief	A function that makes cd precheck for args amount
 * @param	arr array of arguments or options if allowed
 * @return	@c `void`
 */
void	cd_precheck(char **arr, t_minishell *ms)
{
	int	len;

	len = ft_arrlen((void **)arr);
	if (len >= 1 && ft_strlen(arr[0]) > 1 && arr[0][0] == DASH)
	{
		if (arr[0][1] == DASH && arr[0][2] == NULL_TERM)
			return ;
		arr[0][2] = NULL_TERM;
		print_arg_err_msg("cd: `", arr[0], "': options are not supported\n");
		ms->exit_status = CMD_ARG_ERROR;
		return ;
	}
	if (len >= 2)
	{
		print_err_msg("cd: ", "too many arguments\n");
		ms->exit_status = GENERIC_ERROR;
		return ;
	}
}

/**
 * @brief	A function that updates @c `PWD` enviroment variable
 * @param	envp pointer to the environment array
 * @param	ms pointer to the common project @c `t_minishell` structure
 * @return	@c `void`
 */
void	update_env_pwd(char ***envp, t_minishell *ms)
{
	int		position;
	char	*cwd;

	position = env_var(*envp, "PWD=", -1, 4);
	if (position != -1)
	{
		cwd = getcwd(NULL, 0);
		if (!cwd)
			ms->exit_status = GETCWD_ERROR;
		free((*envp)[position]);
		(*envp)[position] = ft_strjoin("PWD=", cwd);
		if (!(*envp)[position])
		{
			free(cwd);
			ms->exit_status = MALLOC_ERR;
		}
		free(cwd);
	}
}

static int	oldpwd_init_when_no_oldpwd_exists(char ***envp, int i,
	t_minishell *ms)
{
	int		len;
	char	**new_env;

	len = ft_arrlen((void **)*envp);
	if (add_to_env_list_new_env_creation(*envp, &new_env, &i, &len)
		== MALLOC_ERR)
		return (MALLOC_ERR);
	new_env[len + i] = ft_strjoin("OLDPWD=", ms->pwd);
	if (!new_env[len + i])
		return (MALLOC_ERR);
	*envp = new_env;
	return (SUCCESS);
}

/**
 * @brief	A function that updates @c `PWD` enviroment variable
 * @param	envp pointer to the environment array
 * @param	ms pointer to the common project @c `t_minishell` structure
 * @return	@c `void`
 */
void	update_env_oldpwd(char ***envp, t_minishell *ms)
{
	int		position;

	position = env_var(*envp, "OLDPWD=", -1, 4);
	if (position != -1)
	{
		free((*envp)[position]);
		(*envp)[position] = ft_strjoin("OLDPWD=", ms->pwd);
		if (!(*envp)[position])
			ms->exit_status = MALLOC_ERR;
	}
	else
		ms->exit_status = oldpwd_init_when_no_oldpwd_exists(envp, 1, ms);
}
