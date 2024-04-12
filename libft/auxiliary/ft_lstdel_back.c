/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dshatilo <dshatilo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 15:05:09 by dshatilo          #+#    #+#             */
/*   Updated: 2024/04/11 10:04:42 by dshatilo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	ft_lstdel_back(t_list **lst, void (*del)(void*))
{
	t_list	*curr;

	if (!lst || !*lst)
		return ;
	curr = *lst;
	if (curr->next == NULL)
	{
		del(curr->content);
		free(curr);
		*lst = NULL;
	}
	while ((curr->next)->next != NULL)
		curr = curr->next;
	del((curr->next)->content);
	free(curr->next);
	curr->next = NULL;
}
