/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_main.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dshatilo <dshatilo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 15:09:34 by dshatilo          #+#    #+#             */
/*   Updated: 2024/02/21 16:53:13 by dshatilo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

int	main(void)
{
	int				status;
	t_node			*node;
	// t_cmd_simple	*t;

	char str[1000] = "((cmd || cmd ) > out | cmd) && cmd";
	node = NULL;
	status = create_tree(str, &node);
	// t = (t_cmd_simple *)node->right;
	printf("%d!\n", status);
	return (0);
}
