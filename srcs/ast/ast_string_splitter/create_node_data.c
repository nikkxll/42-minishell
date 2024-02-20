/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_node_data.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnikifor <dnikifor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 12:46:43 by dnikifor          #+#    #+#             */
/*   Updated: 2024/02/20 14:18:16 by dnikifor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../headers/minishell.h"

int	set_node_data(t_node_data **node, char *str, int point, int type)
{
	t_node_data	*new_node;

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
