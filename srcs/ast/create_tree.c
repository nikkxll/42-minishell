/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_tree.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dshatilo <dshatilo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 13:40:06 by dshatilo          #+#    #+#             */
/*   Updated: 2024/02/16 13:41:03 by dshatilo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

t_bool	create_tree(char *str, t_node **root)
{
	t_node_data	*data;
	t_bool		status;

	data = check_type(str);
	if (data == NULL)
		return (false);
	if (create_node(data, root) == false)
		return (false);
	if (data->type > 2)
		do_cmd();
	else
	{
		status = create_tree(data->str_left, (*root)->left);
		if (status == true)
			status = create_tree(data->str_right, (*root)->right);
		
		if (status == false)
		{
			; //free_root
			return (false);
		}
	}
	return (true);
}