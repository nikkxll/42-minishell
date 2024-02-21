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

int	command_block(t_node_data **node, char *str, int type, int i)
{
	if (brackets_search(str))
		return (set_node_data_command_with_brackets(node, str,
				(int)ft_strlen(str), T_COMMAND_BR));
	return (0);
}

int	command_without_bracket_block(t_node_data **node, char *str, int type,
		int i)
{
	if (redir_search(str))
		return (set_node_data_command_without_brackets(node, str,
				(int)ft_strlen(str), T_COMMAND));
	return (0);
}
