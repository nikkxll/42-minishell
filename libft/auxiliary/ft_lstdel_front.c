/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel_front.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dshatilo <dshatilo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 15:05:09 by dshatilo          #+#    #+#             */
/*   Updated: 2024/04/11 12:40:55 by dshatilo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	ft_lstdel_front(t_list **lst, void (*del)(void*))
{
	t_list	*new_top;

	if (!lst || !*lst)
		return ;
	new_top = (*lst)->next;
	del((*lst)->content);
	free(*lst);
	*lst = new_top;
}
