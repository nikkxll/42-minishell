/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_3d_array.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnikifor <dnikifor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 19:37:20 by dnikifor          #+#    #+#             */
/*   Updated: 2024/03/14 19:38:01 by dnikifor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	ft_free_3d_array(void *ptr)
{
	void	***arr;
	size_t	i;

	arr = (void ***)ptr;
	i = 0;
	while (arr[i])
		ft_free_2d_array(arr[i++]);
	free(arr);
}
