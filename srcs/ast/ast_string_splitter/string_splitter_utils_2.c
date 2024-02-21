/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_splitter_utils_2.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnikifor <dnikifor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 13:54:40 by dnikifor          #+#    #+#             */
/*   Updated: 2024/02/21 14:32:17 by dnikifor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../headers/minishell.h"

char	*command_part(char *str, int *i, int *j, int quote_type)
{
	while (str[*i] != NULL_TERM)
	{
		check_if_inside_quotes_with_incr(str, i, &quote_type);
		if (!quote_type)
		{
			if (str[*i] == O_ROUND)
			{
				*j = *i + 1;
				while (str[*i] != C_ROUND)
					(*i)++;
				if (str[*i] == C_ROUND)
				{
					str[(*i)++] = NULL_TERM;
					return (str);
				}
			}
			(*i)++;
		}
		else
			(*i)++;
	}
	return (NULL);
}

static void	modificate_str_utils(char *str, char *r, int *i, int *j)
{
	r[*j] = str[*i];
	str[*i] = SPACE;
	(*j)++;
	(*i)++;
}

int	modificate_str_command_without_br(char *str, char **redir, int i,
			int j)
{
	char	*r;

	r = (char *)ft_calloc((int)ft_strlen(str), sizeof(char));
	if (!r)
		return (-1);
	while (str[i++] != NULL_TERM)
	{
		while (str[i] != REDIR_L && str[i] != REDIR_R && str[i] != NULL_TERM)
			i++;
		if (str[i] == REDIR_L || str[i] == REDIR_R)
		{
			while ((str[i] == REDIR_L || str[i] == REDIR_R
					|| str[i] == SPACE) && str[i] != NULL_TERM)
				modificate_str_utils(str, r, &i, &j);
			while (str[i] != SPACE && str[i] != NULL_TERM)
				modificate_str_utils(str, r, &i, &j);
		}
	}
	*redir = r;
	return (1);
}

int	brackets_search(char *str)
{
	int	i;
	int	quote_type;
	int	key;

	i = 0;
	quote_type = 0;
	key = 0;
	while (str[i] != NULL_TERM)
	{
		check_if_inside_quotes_with_incr(str, &i, &quote_type);
		if (!quote_type)
		{
			if (str[i] == O_ROUND)
				key++;
			i++;
		}
		else
			i++;
	}
	return (key > 0);
}

int	redir_search(char *str)
{
	int	i;
	int	quote_type;
	int	key;

	i = 0;
	quote_type = 0;
	key = 0;
	while (str[i] != NULL_TERM)
	{
		check_if_inside_quotes_with_incr(str, &i, &quote_type);
		if (!quote_type)
		{
			if (str[i] == REDIR_L || str[i] == REDIR_R)
				key++;
			i++;
		}
		else
			i++;
	}
	return (key > 0);
}

int	ft_error(char *message, int code)
{
	ft_putendl_fd(message, 2);
	return (code);
}
