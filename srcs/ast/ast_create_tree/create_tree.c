/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_tree.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnikifor <dnikifor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 13:40:06 by dshatilo          #+#    #+#             */
/*   Updated: 2024/02/22 19:58:11 by dnikifor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../headers/minishell.h"

t_bool	get_type(char *str, t_node_data **data);

t_bool	create_tree(char *str, t_node **root)
{
	t_node_data	*data;
	t_bool		status;
	int			type;

	status = get_type(str, &data);
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

t_bool	get_type(char *str, t_node_data **data)
{
	int	status;

	status = string_splitter(data, str, T_AND, ft_strlen(str) - 1);
	return (status);
}
