/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_splitter_blocks_command.c                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnikifor <dnikifor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 13:55:41 by dnikifor          #+#    #+#             */
/*   Updated: 2024/02/21 14:30:43 by dnikifor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../headers/minishell.h"

int	command_block(t_node_data **node, char *str, int type)
{
	if (brackets_search(str))
		return (set_node_data_command_br(node, str, type));
	return (0);
}

int	command_without_bracket_block(t_node_data **node, char *str, int type)
{
	if (redir_search(str))
		return (set_node_data_command(node, str, type));
	return (0);
}
