/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_redirect.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dshatilo <dshatilo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 16:08:20 by dshatilo          #+#    #+#             */
/*   Updated: 2024/03/01 19:06:19 by dshatilo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

// validate_redirect<redirect>     ::=  ( '<' | '>' | '<<' | '>>' ) <word>

char	*validate_redirect(char *str)
{
	int		i;
	t_bool	status;

	i = 0;
	while (*str == SPACE)
		str++;
	if (ft_strncmp(">>", str, 2) == 0)
		str = str + 2;
	else if (ft_strncmp("<<", str, 2) == 0)
		str = str + 2;
	else if (ft_strncmp(">", str, 1) == 0)
		str = str + 1;
	else if (ft_strncmp("<", str, 1) == 0)
		str = str + 1;
	status = true;
	while (status)
	{
		status = is_word(*str);
		str++;
	}
	return (str);
}
