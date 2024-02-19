/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_meta.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnikifor <dnikifor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 17:34:13 by dnikifor          #+#    #+#             */
/*   Updated: 2024/02/19 17:57:31 by dnikifor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

static int	check_if_redirect_file_pattern_complied_sequel(char *str, int i)
{
	while (str[i] == SPACE && str[i] != NULL_TERM)
		i++;
	if (str[i] == REDIR_R || str[i] == REDIR_L || str[i] == NULL_TERM)
		return (INVALID);
	return (VALID);
}

int	check_if_redirect_file_pattern_complied(char *str, int quote_type, int i)
{
	while (str[i] != NULL_TERM)
	{
		check_if_inside_quotes_with_incr(str, &i, &quote_type);
		if (!quote_type)
		{
			if ((str[i] == REDIR_R && str[i + 1] != REDIR_R)
				|| (str[i] == REDIR_L && str[i + 1] != REDIR_L))
			{
				if (check_if_redirect_file_pattern_complied_sequel(str, i + 1))
					return (INVALID);
			}
			else if ((str[i] == REDIR_R && str[i + 1] == REDIR_R)
				|| (str[i] == REDIR_L && str[i + 1] == REDIR_L))
			{
				if (check_if_redirect_file_pattern_complied_sequel(str, i + 2))
					return (INVALID);
				i++;
			}
			i++;
		}
		else
			i++;
	}
	return (VALID);
}

int	check_if_redirects_and_or_are_correct(char *str, int first,
	int second, int quote_type)
{
	int	i;

	i = 0;
	while (str[i] != NULL_TERM)
	{
		check_if_inside_quotes_with_incr(str, &i, &quote_type);
		if (!quote_type)
		{
			if ((str[i] == first && str[i + 1] == second)
				|| (str[i] == second && str[i + 1] == first))
				return (INVALID);
			if ((str[i] == second && str[i + 1] == second)
				|| (str[i] == first && str[i + 1] == first))
			{
				if (str[i + 2] == second || str[i + 2] == first)
					return (INVALID);
			}
			i++;
		}
		else
			i++;
	}
	return (VALID);
}
