/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_tree.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dshatilo <dshatilo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 13:40:06 by dshatilo          #+#    #+#             */
/*   Updated: 2024/02/21 14:46:41 by dshatilo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

int	*test(char *str, t_node_data **data);

t_bool	create_tree(char *str, t_node **root)
{
	t_node_data	*data;
	t_bool		status;
	int			type;

	status = test(str, &data);
	if (status == false)
		return (status);
	if (create_node(data, root) == false)
		return (false);
	type = data->type;
	if (type == T_AND || type == T_OR || type == T_PIPE)
		status = add_and_or_pipe_trees(data, root);
	else if (type == T_BRACKET)
		status = add_bracket(data, root);
	else if (type == T_COMMAND)
		status = add_command(data, root);
	else if (type == T_COMMAND_BR)
		status = add_command_br(data, root);
	else if (type == T_CMD_SIMPLE)
		status = add_cmd_simple(data, root);
	free_node_data(data);
	if (status == false)
		free_tree(root);
	return (status);
}
