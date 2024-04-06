/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_core.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnikifor <dnikifor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 15:22:52 by dnikifor          #+#    #+#             */
/*   Updated: 2024/04/06 12:50:14 by dnikifor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../headers/minishell.h"

/**
 * @brief	A function that handles change of directory to @c `OLDPWD`
 * @param	ms pointer to the common project @c `t_minishell` structure
 * @return	@c `void`
 */
static void	handle_cd_oldpwd(t_minishell *ms)
{
	int		env_variable;

	env_variable = env_var(ms->env, "OLDPWD=", -1, 7);
	if (env_variable == -1)
	{
		print_err_msg("cd: ", "OLDPWD not set\n");
		ms->exit_status = GENERIC_ERROR;
		return ;
	}
	else if (chdir((ms->env)[env_variable] + 7) != 0)
	{
		perror_err_msg("cd: ", (ms->env)[env_variable] + 7);
		ms->exit_status = GENERIC_ERROR;
		return ;
	}
	else
		ft_printf("%s\n", (ms->env)[env_variable] + 7);
}

/**
 * @brief	A function that handles change of directory to @c `HOME`
 * @param	ms pointer to the common project @c `t_minishell` structure
 * @return	@c `void`
 */
static void	handle_cd_home(t_minishell *ms)
{
	int		env_variable;

	env_variable = env_var(ms->env, "HOME=", -1, 5);
	if (env_variable == -1)
	{
		print_err_msg("cd: ", "HOME not set\n");
		ms->exit_status = GENERIC_ERROR;
		return ;
	}
	else if (chdir((ms->env)[env_variable] + 5) != 0)
	{
		perror_err_msg("cd: ", (ms->env)[env_variable] + 5);
		ms->exit_status = GENERIC_ERROR;
		return ;
	}
}

/**
 * @brief	A function that runs cd built-in command
 * @param	arr array of arguments or options if allowed
 * @param	ms pointer to the common project @c `t_minishell` structure
 * @param	status initialization for the local variable
 * @return	@c `void`
 */
void	run_cd(char **arr, t_minishell *ms, int status)
{
	cd_precheck(arr, ms);
	if (ms->exit_status != SUCCESS)
		return ;
	if (ft_arrlen((void **)arr) == 0 || !ft_strncmp(arr[0], "--", 2))
		handle_cd_home(ms);
	else if (!ft_strncmp(arr[0], "-", ft_strlen(arr[0]))
		&& ft_strlen(arr[0]) > 0)
		handle_cd_oldpwd(ms);
	else if (ft_strlen(arr[0]) == 0)
		status = chdir(".");
	else
		status = chdir(arr[0]);
	if (status != 0)
	{
		perror_err_msg("cd: ", arr[0]);
		ms->exit_status = GENERIC_ERROR;
		return ;
	}
	else if (ms->exit_status != SUCCESS)
		return ;
	struct_pwd_and_full_oldpwd_update(NULL, ms);
	if (ms->exit_status != SUCCESS)
		return ;
	update_env_pwd(ms);
}
