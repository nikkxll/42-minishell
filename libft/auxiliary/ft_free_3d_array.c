/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_3d_array.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnikifor <dnikifor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 19:37:20 by dnikifor          #+#    #+#             */
/*   Updated: 2024/03/15 16:01:09 by dnikifor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	ft_free_3d_array(void *ptr, int mode)
{
	void	***arr;
	void	(*f)(void *);
	size_t	i;

	if (mode == 0)
		f = ft_free_2d_array;
	else
		f = free;
	arr = (void ***)ptr;
	i = 0;
	while (arr[i])
		f(arr[i++]);
	free(arr);
}
