/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_node_data.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnikifor <dnikifor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 12:46:43 by dnikifor          #+#    #+#             */
/*   Updated: 2024/02/21 14:32:02 by dnikifor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../headers/minishell.h"

int	set_node_data_command_without_brackets(t_node_data **node, char *str,
		int point, int type)
{
	t_node_data	*new_node;
	char		*redir;
	int			status;

	new_node = ft_calloc(1, sizeof(node));
	if (!new_node)
	{
		*node = new_node;
		return (-1);
	}
	status = modificate_str_command_without_br(str, &redir, 0, 0);
	if (status == -1)
	{
		*node = new_node;
		return (-1);
	}
	new_node->str_left = redir;
	new_node->str_right = str;
	new_node->type = type;
	*node = new_node;
	return (1);
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
	{
		*node = new_node;
		return (-1);
	}
	new_node->str_left = str;
	new_node->str_right = NULL;
	new_node->str_right = str + point + 1;
	new_node->type = type;
	*node = new_node;
	return (1);
}

int	set_node_data_command_with_brackets(t_node_data **node, char *str,
		int point, int type)
{
	t_node_data	*new_node;
	int			i;
	int			j;

	i = 0;
	j = 0;
	new_node = ft_calloc(1, sizeof(node));
	if (!new_node)
	{
		*node = new_node;
		return (-1);
	}
	new_node->str_left = command_part(str, &i, &j, 0) + i;
	new_node->str_right = str + j;
	new_node->type = type;
	*node = new_node;
	return (1);
}
