/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnikifor <dnikifor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 21:21:43 by dshatilo          #+#    #+#             */
/*   Updated: 2024/04/03 13:59:53 by dnikifor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../headers/minishell.h"

int	parse_cmd(char *cmd, char ***res, char **envp)
{
	char	**arr;
	int		i;
	int		status;

	arr = wrapper_ft_split_with_quotes(cmd);
	if (!arr)
		return (MALLOC_ERR);
	i = 0;
	status = 0;
	while (arr[i] && status == 0)
		status = dollar_sign_expansion(&arr[i++], envp, 0);
	if (status == 0)
		status = array_build_before_wc(&arr, -1, -1, -1);
	if (status == 0)
		status = wildcards(&arr);
	if (status != 0 && arr != NULL)
		ft_free_2d_array(arr);
	if (status == 0)
	{
		processing(arr, 0);
		*res = arr;
	}
	return (status);
}
