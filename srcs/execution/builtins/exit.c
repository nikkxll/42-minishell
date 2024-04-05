/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnikifor <dnikifor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 15:11:23 by dnikifor          #+#    #+#             */
/*   Updated: 2024/04/04 17:42:27 by dnikifor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../headers/minishell.h"

/**
 * @brief	Auxiliary function that checks ft_atol result if it is equal to
 * @c `0`
 * @param	str string to check
 * @return	@c `true` if the string is in a wrong format (not @c `0` means
 * ft_atol signal about the error)
 * @c `false` if the string is in a right format (means ft_atol is actually
 * equal to @c `0`)
 */
static t_bool	zero_check(char *str)
{
	while ((*str >= 9 && *str <= 13) || *str == 32)
		str++;
	if (*str == '+' || *str == '-')
		str++;
	while (*str == '0')
		str++;
	while ((*str >= 9 && *str <= 13) || *str == 32)
		str++;
	if (*str != NULL_TERM)
		return (true);
	return (false);
}

/**
 * @brief	A function that runs exit built-in command
 * @param	arr array of arguments or options if allowed
 * @param	ms pointer to the common project @c `t_minishell` structure
 * @param	num number that ft_atol returns
 * @return	@c `void`
 */
void	run_exit(char **arr, t_minishell *ms, long num)
{
	if (ft_arrlen((void **)arr) > 1)
	{
		if (ms->is_parent == true)
			ft_putstr_fd("exit\n", 1);
		print_err_msg("exit: ", "too many arguments\n");
		ms->exit_status = GENERIC_ERROR;
		return ;
	}
	else if (!*arr)
		ms->exit_status = SUCCESS;
	else
	{
		num = ft_atol(arr[0]);
		if ((zero_check(arr[0]) && num == 0) || check_for_non_digits(arr[0]))
		{
			print_arg_err_msg("exit: ", arr[0],
				": numeric argument required\n");
			ms->exit_status = UNEXPECTED_EXIT;
		}
		else
			ms->exit_status = (unsigned char)num;
	}
	if (ms->is_parent == true)
		ft_putstr_fd("exit\n", 1);
	exit(ms->exit_status);
}
