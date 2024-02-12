/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dshatilo <dshatilo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 11:57:46 by dshatilo          #+#    #+#             */
/*   Updated: 2023/11/28 11:50:27 by dshatilo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	ft_lstsize(t_list *lst)
{
	size_t	len;
	t_list	*curr;

	if (!lst)
		return (0);
	curr = lst;
	len = 1;
	while (curr->next)
	{
		len++;
		curr = curr->next;
	}
	return (len);
}
