/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_tree.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnikifor <dnikifor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 13:40:06 by dshatilo          #+#    #+#             */
/*   Updated: 2024/04/18 23:52:06 by dnikifor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

t_bool	get_type(char *str, t_node_info **info);

/**
 * @brief	Recursively creates binary tree. The function calls @c `get_type`
 * functions to determine the type of the current node and creates node
 * accordingly. If error occurs, it calls `free_tree` function and frees
 * allocated memory.
 * @param	str String with command pipeline.
 * @param	root A double pointer indicating where to save the current node.
 * @param	hd_num pointer to the heredoc number.
 * @param	ms pointer to the common project @c `t_minishell` structure.
 * @return	@c `0` if successful, @c `MALLOC_ERR` if an error occurs.
 */
int	create_tree(char *str, t_node **root, int *hd_num, t_minishell *ms)
{
	t_node_info	*info;
	t_bool		status;
	int			type;

	status = get_type(str, &info);
	if (status == false)
		return (MALLOC_ERR);
	if (create_node(info, root) == false)
		return (MALLOC_ERR);
	type = info->type;
	if (type == T_AND || type == T_OR || type == T_PIPE)
		status = add_and_or_pipe_trees(info, root, hd_num, ms);
	else if (type == T_BRACKET)
		status = add_bracket(info, root, hd_num, ms);
	else if (type == T_COMMAND)
		status = add_command(info, root, hd_num, ms);
	else if (type == T_COMMAND_BR)
		status = add_command_br(info, root, hd_num, ms);
	free(info);
	if (status != SUCCESS)
	{
		free_tree(root);
		return (status);
	}
	return (SUCCESS);
}

t_bool	get_type(char *str, t_node_info **info)
{
	int	status;

	status = lexer(info, str, T_AND, ft_strlen(str) - 1);
	return (status);
}
