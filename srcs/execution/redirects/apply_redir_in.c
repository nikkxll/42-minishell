/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   apply_redir_in.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnikifor <dnikifor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 23:03:41 by dshatilo          #+#    #+#             */
/*   Updated: 2024/04/05 19:23:19 by dnikifor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../headers/minishell.h"

int	apply_redir_in(char *redir, t_minishell *ms, int *in)
{
	int		status;
	int		fd;

	close(*in);
	while (*redir == SPACE)
		redir++;
	status = check_redir(&redir, ms);
	if (status != 0)
		return (status);
	fd = open(redir, O_RDONLY);
	if (fd != -1)
		*in = fd;
	else
	{
		status = GENERIC_ERROR;
		perror("\033[0;31me-bash\033[0;0m"); //edit error message!
	}
	free(redir);
	return (status);
}
