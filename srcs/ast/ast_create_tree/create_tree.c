/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_tree.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dshatilo <dshatilo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 13:40:06 by dshatilo          #+#    #+#             */
/*   Updated: 2024/04/07 02:42:22 by dshatilo         ###   ########.fr       */
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
 * @return	@c `0` if successful, @c `MALLOC_ERR` if an error occurs.
 */
int	create_tree(char *str, t_node **root)
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
		status = add_and_or_pipe_trees(info, root);
	else if (type == T_BRACKET)
		status = add_bracket(info, root);
	else if (type == T_COMMAND)
		status = add_command(info, root);
	else if (type == T_COMMAND_BR)
		status = add_command_br(info, root);
	free(info);
	if (status == MALLOC_ERR)
	{
		free_tree(root);
		return (MALLOC_ERR);
	}
	return (0);
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
// 	if (t == T_REDIR)
// 		return ("redir");
// 	return (NULL);
// }

// void	preorder(t_node	*tree)
// {
// 	int	type;

// 	type = tree->type;
// 	if (type == T_AND || type == T_OR || type == T_PIPE || type == T_COMMAND_BR)
// 	{
// 		printf("[t:%s, t_l:%d, t_r:%d] \n", return_type(tree->type),
// 			tree->left->type, tree->right->type);
// 		preorder(tree->left);
// 		preorder(tree->right);
// 	}
// 	else if (type == T_COMMAND)
// 	{
// 		printf("[t:%s, t_l:%d, cmd:%s]  \n", return_type(tree->type),
// 			((t_command *)tree)->redir->type, ((t_command *)tree)->cmd);
// 		preorder(tree->left);
// 	}
// 	else if (type == T_BRACKET)
// 	{
// 		printf("[t:%s, t_l:%d]  \n", return_type(tree->type), tree->left->type);
// 		preorder(tree->left);
// 	}
// 	else if (type == T_REDIR)
// 		printf("[t:%s, redir:%s]  \n", return_type(tree->type),
// 			((t_redir *)tree)->str);
// }

// int	main(int argc, char **argv)
// {
// 	int				status;
// 	t_node			*tree;
// 	char			*str;

// 	str = argv[1];

// 	tree = NULL;
// 	status = create_tree(str, &tree);
// 	printf("->%d\n", status);
// 	if (status != 0)
// 		printf("Can't create tree!\n");
// 	preorder(tree);
// 	printf("\n");
// 	free_tree(&tree);
// 	(void)argc;
// 	return (0);
// }
