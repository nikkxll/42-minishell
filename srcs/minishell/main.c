/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnikifor <dnikifor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 11:53:09 by dnikifor          #+#    #+#             */
/*   Updated: 2024/08/22 13:03:58 by dnikifor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

volatile sig_atomic_t	g_sgnl;

int	main(void)
{
	t_minishell	*ms;
	int			last_status;

	signal_interceptor(IGNORE);
	toggler(IMPLICIT);
	ft_printf("\033[2J\033[H");
	initialize_minishell(&ms);
	run_minishell(&ms);
	last_status = ms->exit_status;
	rl_clear_history();
	save_history_to_file(ms);
	ft_free_minishell(ms);
	ms = NULL;
	return (last_status);
}
