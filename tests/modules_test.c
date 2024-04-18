/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mains.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnikifor <dnikifor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 10:52:51 by dshatilo          #+#    #+#             */
/*   Updated: 2024/04/18 23:36:10 by dnikifor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//BNF_SYNTAX_VALIDATOR - VALIDATE INPUT

/*
int	main(int argc, char **argv)
{
	int	is_valid;

	if (argc != 2)
	{
		ft_printf("INCORRECT NUMBER OF ARGUMENTS!\n");
		return (1);
	}
	is_valid = validate_input(argv[1]);
	if (is_valid == 0)
		ft_printf("Input is correct!\n");
	(void)argc;
	return (0);
}
*/

//AST_PARSER - CREATE TREE
/*

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
	if (t == T_REDIR)
		return ("redir");
	return (NULL);
}

void	preorder(t_node	*tree)
{
	int	type;

	type = tree->type;
	if (type == T_AND || type == T_OR || type == T_PIPE || type == T_COMMAND_BR)
	{
		printf("[t:%s, t_l:%d, t_r:%d] \n", return_type(tree->type),
			tree->left->type, tree->right->type);
		preorder(tree->left);
		preorder(tree->right);
	}
	else if (type == T_COMMAND)
	{
		printf("[t:%s, t_l:%d, cmd:%s]  \n", return_type(tree->type),
			((t_command *)tree)->redir->type, ((t_command *)tree)->cmd);
		preorder(tree->left);
	}
	else if (type == T_BRACKET)
	{
		printf("[t:%s, t_l:%d]  \n", return_type(tree->type), tree->left->type);
		preorder(tree->left);
	}
	else if (type == T_REDIR)
		printf("[t:%s, redir:%s]  \n", return_type(tree->type),
			((t_redir *)tree)->str);
}

int	main(int argc, char **argv)
{
	int				status;
	t_node			*tree;
	char			*str;

	str = argv[1];

	tree = NULL;
	status = create_tree(str, &tree);
	printf("->%d\n", status);
	if (status != 0)
		printf("Can't create tree!\n");
	preorder(tree);
	printf("\n");
	free_tree(&tree);
	(void)argc;
	return (0);
}
*/
