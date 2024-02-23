/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_node_data.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dshatilo <dshatilo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 18:49:29 by dshatilo          #+#    #+#             */
/*   Updated: 2024/02/23 16:00:48 by dshatilo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../headers/minishell.h"
/**
 * @brief	Frees the memory allocated for `t_node_data` structure .
 * 
 * @param	data A pointer to the structure containing
 * 			information about the type of current node and its children.
 * @note	If the type of the node is @c `T_COMMAND`, the function also frees
 * 			the `char *str_left` allocated in the string_splitter part.
 */
void	free_node_data(t_node_data *data)
{
	if (data->type == T_COMMAND)
		free(data->str_left);
	free(data);
}
