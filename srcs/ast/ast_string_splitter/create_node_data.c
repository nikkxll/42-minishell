/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_node_data.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnikifor <dnikifor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 12:46:43 by dnikifor          #+#    #+#             */
/*   Updated: 2024/02/20 19:24:10 by dnikifor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../headers/minishell.h"

char	*compound_part(char *str, int *i, int *j, int quote_type)
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

int	set_node_data(t_node_data **node, char *str, int point, int type)
{
	t_node_data	*new_node;

	if (type == T_AND || type == T_OR)
	{
		str[point] = NULL_TERM;
		str[point - 1] = NULL_TERM;
	}
	else
		str[point] = NULL_TERM;
	new_node = ft_calloc(1, sizeof(node));
	if (!new_node)
		return (-1);
	new_node->str_left = str;
	new_node->str_right = NULL;
	new_node->str_right = str + point + 1;
	new_node->type = type;
	*node = new_node;
	return (1);
}

int	set_node_data_compound_with_brackets(t_node_data **node, char *str,
		int point, int type)
{
	t_node_data	*new_node;
	int			i;
	int			j;

	i = 0;
	j = 0;
	new_node = ft_calloc(1, sizeof(node));
	if (!new_node)
		return (-1);
	new_node->str_left = compound_part(str, &i, &j, 0) + i;
	i = 0;
	j = 0;
	new_node->str_right = compound_part(str, &i, &j, 0) + j;
	new_node->type = type;
	*node = new_node;
	return (1);
}
