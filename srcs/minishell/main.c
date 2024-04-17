/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dshatilo <dshatilo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 11:53:09 by dnikifor          #+#    #+#             */
/*   Updated: 2024/04/17 20:17:43 by dshatilo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

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
