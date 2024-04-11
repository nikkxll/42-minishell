/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnikifor <dnikifor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 11:53:09 by dnikifor          #+#    #+#             */
/*   Updated: 2024/04/11 15:28:11 by dnikifor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

int	main(void)
{
	t_minishell	*ms;
	int			last_status;

	signal_chars_toggler(0);
	catch_signal(INTERACTIVE);
	initialize_minishell(&ms);
	run_minishell(ms);
	last_status = ms->exit_status;
	rl_clear_history();
	ft_free_minishell(ms);
	return (last_status);
}
// int	main(void)
// {


// 	signal_chars_toggler(0);
// 	catch_signal(INTERACTIVE);
// 	while(1)
// 	{
// 		getchar();
// 		ft_printf(">");
// 	}
// 	return (0);
// }