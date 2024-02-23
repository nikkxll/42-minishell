/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dshatilo <dshatilo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 15:09:34 by dshatilo          #+#    #+#             */
/*   Updated: 2024/03/05 10:52:43 by dshatilo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

char	*return_type(int t)
{
	if (t == T_AND)
		return ("and");
	if (t == T_OR)
		return ("or");
	if (t == T_PIPE)
		return ("pipe");
	if (t == T_BRACKET)
		return ("bracket");
	if (t == T_COMMAND)
		return ("command");
	if (t == T_COMMAND_BR)
		return ("command_br");
	if (t == T_CMD_SIMPLE)
		return ("cmd_s");
	if (t == T_REDIR)
		return ("redir");
	return (NULL);
}

void	inorder(t_node	*tree)
{
	int	type;

	type = tree->type;
	if (type == T_AND || type == T_OR || type == T_PIPE
		|| type == T_COMMAND || type == T_COMMAND_BR)
	{
		inorder(tree->left);
		printf("[t:%s, t_l:%d, t_r:%d] ", return_type(tree->type), tree->left->type, tree->right->type);
		inorder(tree->right);
	}
	else if (type == T_BRACKET)
	{
		inorder(tree->left);
		printf("[t:%s, t_l:%d] ", return_type(tree->type), tree->left->type);
	}
	else if (type == T_CMD_SIMPLE)
		printf("[t:%s, cmd:%s] ", return_type(tree->type), ((t_cmd_simple *)tree)->cmd);
	else if (type == T_REDIR)
		printf("[t:%s, redir:%s] ", return_type(tree->type), ((t_redir *)tree)->str);
}

int	main(int argc, char **argv)
{
	int				status;
	t_node			*tree;
	char			*str;

	str = argv[1];

	tree = NULL;
	status = create_tree(str, &tree);
	printf("%d!\n", status);
	inorder(tree);
	free_tree(&tree);
	(void)argc;
	return (0);
}
