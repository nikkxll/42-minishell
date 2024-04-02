/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_tree.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnikifor <dnikifor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 13:40:06 by dshatilo          #+#    #+#             */
/*   Updated: 2024/04/02 13:53:23 by dnikifor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../headers/minishell.h"

t_bool	get_type(char *str, t_node_info **info);

/**
 * @brief	Recursively creates binary tree. The function calls @c `get_type`
 * 			functions to determine the type of the current node and creates node
 * 			accordingly. If error occurs, it calls `free_tree` function and frees
 * 			allocated memory.
 * 
 * @param	str String with command pipeline.
 * @param	root A double pointer indicating where to save the current node.
 * @return	@c `true` if successful, @c `false` if an error occurs.
 */
t_bool	create_tree(char *str, t_node **root)
{
	t_node_info	*info;
	t_bool		status;
	int			type;

	status = get_type(str, &info);
	if (status == false)
		return (status);
	if (create_node(info, root) == false)
		return (false);
	type = info->type;
	if (type == T_AND || type == T_OR || type == T_PIPE)
		status = add_and_or_pipe_trees(info, root);
	else if (type == T_BRACKET)
		status = add_bracket(info, root);
	else if (type == T_COMMAND)
		status = add_command(info, root);
	else if (type == T_COMMAND_BR)
		status = add_command_br(info, root);
	else if (type == T_CMD_SIMPLE)
		status = add_cmd_simple(info, root);
	free(info);
	if (status == false)
		free_tree(root);
	return (status);
}

t_bool	get_type(char *str, t_node_info **info)
{
	int	status;

	status = string_splitter(info, str, T_AND, ft_strlen(str) - 1);
	return (status);
}

// char	*return_type(int t)
// {
// 	if (t == T_AND)
// 		return ("and");
// 	if (t == T_OR)
// 		return ("or");
// 	if (t == T_PIPE)
// 		return ("pipe");
// 	if (t == T_BRACKET)
// 		return ("bracket");
// 	if (t == T_COMMAND)
// 		return ("command");
// 	if (t == T_COMMAND_BR)
// 		return ("command_br");
// 	if (t == T_CMD_SIMPLE)
// 		return ("cmd_s");
// 	if (t == T_REDIR)
// 		return ("redir");
// 	return (NULL);
// }

// void	preorder(t_node	*tree)
// {
// 	int	type;

// 	type = tree->type;
// 	if (type == T_AND || type == T_OR || type == T_PIPE
// 		|| type == T_COMMAND || type == T_COMMAND_BR)
// 	{
// 		printf("[t:%s, t_l:%d, t_r:%d] \n", return_type(tree->type),
// 		tree->left->type, tree->right->type);
// 		preorder(tree->left);
// 		preorder(tree->right);
// 	}
// 	else if (type == T_BRACKET)
// 	{
// 		printf("[t:%s, t_l:%d]  \n", return_type(tree->type), tree->left->type);
// 		preorder(tree->left);
// 	}
// 	else if (type == T_CMD_SIMPLE)
// 		printf("[t:%s, cmd:%s]  \n", return_type(tree->type),
// 		((t_cmd_simple *)tree)->cmd);
// 	else if (type == T_REDIR)
// 		printf("[t:%s, redir:%s]  \n", return_type(tree->type),
// 		((t_redir *)tree)->str);
// }

// int	main(int argc, char **argv)
// {
// 	int				status;
// 	t_node			*tree;
// 	char			*str;

// 	str = argv[1];

// 	tree = NULL;
// 	status = create_tree(str, &tree);
// 	if (status == false)
// 		printf("Can't create tree!\n");
// 	preorder(tree);
// 	printf("\n");
// 	free_tree(&tree);
// 	(void)argc;
// 	return (0);
// }
