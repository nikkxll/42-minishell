/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize_minishell.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dshatilo <dshatilo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 11:53:09 by dnikifor          #+#    #+#             */
/*   Updated: 2024/04/11 11:12:38 by dshatilo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

void	terminate_minishell(t_minishell **ms, int status);

/**
 * @brief	Initializing a minishell environment
 * @note	This function initializes a minishell environment by allocating
 * memory for a minishell structure @c `t_minishell`, populating it with
 * environment variables, and initializing the present working directory
 * @c `pwd` and the shell level @c `shlvl`. If any memory allocation fails
 * during initialization, the function terminates the minishell and exits with
 * an appropriate error status code
 * @param	ms Pointer to a pointer to a minishell structure @c `t_minishell`.
 *	This pointer will be updated to point to the newly initialized minishell
 * @return	@c `void`
 */
void	initialize_minishell(t_minishell **ms)
{
	extern char	**environ;
	int			status;

	status = 0;
	*ms = ft_calloc(1, sizeof(t_minishell));
	if (!*ms)
		status = MALLOC_ERR;
	if (status == 0)
	{
		(*ms)->env = cpy_env(environ);
		if (!(*ms)->env)
			status = MALLOC_ERR;
	}
	if (status == 0)
		status = pwd_init(&((*ms)->env), &((*ms)->pwd));
	if (status == 0)
		status = shlvl_init(&((*ms)->env));
	if (status == 0)
		init_history(ms);
	if (status != 0)
		terminate_minishell(ms, status);
	(*ms)->is_parent = true;
}

/**
 * @brief	Terminating the minishell environment and exit with an error status
 * @note	This function terminates the minishell environment by
 * freeing allocated memory for the minishell structure @c `t_minishell` and
 * its components. It also prints an error message indicating the failure to
 * initialize the minishell structure before exiting with the specified error
 * status code.
 * @param	ms Pointer to a pointer to a minishell structure @c `t_minishell`
 * @param	status Error status code indicating the reason for termination
 * @return	@c `void`
 */
void	terminate_minishell(t_minishell **ms, int status)
{
	ft_free_minishell(*ms);
	ft_putstr_fd("\033[0;31me-bash:\033[0;0m can't initialize "
		"t_minishell structure\n", STDERR_FILENO);
	exit (status);
}
