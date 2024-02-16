/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_node_data.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dshatilo <dshatilo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 18:49:29 by dshatilo          #+#    #+#             */
/*   Updated: 2024/02/16 13:39:44 by dshatilo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

void	free_node_data(t_node_data *data)
{
	if (data->type > 2)
	{
		free(data->str_left);
		free(data->str_right);
	}
	free(data);
}
