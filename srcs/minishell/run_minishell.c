/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_minishell.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dshatilo <dshatilo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 14:12:15 by dshatilo          #+#    #+#             */
/*   Updated: 2024/04/08 19:18:44 by dshatilo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

int	get_cmdline(char **cmdline, t_minishell *ms);

void	run_minishell(t_minishell *ms)
{
	int		status;
	char	*cmdline;
	t_node	*root;

	while (true)
	{
		status = get_cmdline(&cmdline, ms);
		if (status == EOF)
			break ;
		if (status != 0)
		{
			ms->exit_status = status;
			continue ;
		}
		root = NULL;
		status = create_tree(cmdline, &root);
		if (status != 0)
			ms->exit_status = status;
		if (status == 0)
			ms->exit_status = traverse_tree(&root, ms);
		free(cmdline);
	}
}


int	get_cmdline(char **cmdline, t_minishell *ms)
{
	int		status;
	char	*prompt;

	status = get_prompt(&prompt, ms->exit_status);
	if (status != 0)
		return (status);
	*cmdline = readline(prompt);
	free(prompt);
	if (*cmdline == NULL)
		return (EOF);
	if (ft_strlen(*cmdline) == 0)
	{
		free(*cmdline);
		return (get_cmdline(cmdline, ms));
	}
	add_history(*cmdline);
	status = validate_input(*cmdline);
	if (status != 0)
		free(*cmdline);
	return (status);
}
