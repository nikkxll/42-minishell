/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnikifor <dnikifor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 21:21:43 by dshatilo          #+#    #+#             */
/*   Updated: 2024/04/07 23:25:43 by dnikifor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

int	parse_cmd(char *cmd, char ***res, t_minishell *ms)
{
	char	**arr;
	int		i;
	int		status;

	if (is_blank_string(cmd))
		cmd = "";
	arr = wrapper_ft_split_with_quotes(cmd);
	if (!arr)
		return (MALLOC_ERR);
	i = 0;
	status = 0;
	while (arr[i] && status == 0)
		status = dollar_sign_expansion(&arr[i++], ms->env, ms->exit_status);
	if (status == 0)
		status = array_build_before_wc(&arr, -1, -1, -1);
	if (status == 0)
		status = wildcards(&arr);
	if (status != 0 && arr != NULL)
		ft_free_2d_array(arr);
	if (status == 0)
	{
		remove_quotes_arr(arr, 0);
		*res = arr;
	}
	return (status);
}
