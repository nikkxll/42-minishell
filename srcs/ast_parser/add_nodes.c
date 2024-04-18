/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_nodes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnikifor <dnikifor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 14:44:20 by dshatilo          #+#    #+#             */
/*   Updated: 2024/04/19 12:26:29 by dnikifor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

/**
 * @brief	Functions to add nodes to a binary tree based on the type 
 * of the current node.
 * @param	info A pointer to the structure containing information about
 * the type of current node.
 * @param	root A double pointer indicating where to save the current node.
 * @param	hd_num pointer to the heredoc number
 * @param	ms pointer to the common project @c `t_minishell` structure
 * @return	@c `true` if successful, @c `false` if an error occurs.
 */
int	add_and_or_pipe_trees(t_node_info *info, t_node **root, int *hd_num,
		t_minishell *ms)
{
	int	status;

	status = create_tree(info->str_left, &((*root)->left), hd_num, ms);
	if (status == 0)
		status = create_tree(info->str_right, &((*root)->right), hd_num, ms);
	return (status);
}

int	add_bracket(t_node_info *info, t_node **root, int *hd_num, t_minishell *ms)
{
	int	status;

	status = create_tree(info->str_left, &((*root)->left), hd_num, ms);
	return (status);
}

int	add_command(t_node_info *info, t_node **root, int *hd_num, t_minishell *ms)
{
	int		status;
	t_redir	*redir_node;
	char	**redirs;

	status = prepare_redirects(info->str_left, hd_num, &redirs, ms);
	if (status != SUCCESS)
		return (status);
	redir_node = init_t_redir();
	if (redir_node == NULL)
	{
		if (redirs)
			ft_free_2d_array(redirs);
		return (MALLOC_ERR);
	}
	redir_node->redirs = redirs;
	((t_command *)(*root))->redir = (t_node *)redir_node;
	((t_command *)(*root))->cmd = info->str_right;
	return (0);
}

int	add_command_br(t_node_info *info, t_node **root, int *hd_num,
		t_minishell *ms)
{
	int		status;
	t_redir	*redir_node;
	char	**redirs;

	status = prepare_redirects(info->str_left, hd_num, &redirs, ms);
	if (status != SUCCESS)
		return (status);
	redir_node = init_t_redir();
	if (redir_node == NULL)
	{
		if (redirs)
			ft_free_2d_array(redirs);
		return (MALLOC_ERR);
	}
	redir_node->redirs = redirs;
	(*root)->left = (t_node *)redir_node;
	status = create_tree(info->str_right, &((*root)->right), hd_num, ms);
	return (status);
}
