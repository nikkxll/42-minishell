/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dshatilo <dshatilo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 18:31:00 by dshatilo          #+#    #+#             */
/*   Updated: 2023/11/28 11:50:20 by dshatilo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new;
	t_list	*curr;
	void	*new_c;

	if (!lst || !f || !del)
		return (0);
	new = 0;
	while (lst)
	{
		new_c = f(lst->content);
		curr = ft_lstnew(new_c);
		if (!curr)
		{
			free(new_c);
			ft_lstclear(&new, del);
			return (0);
		}
		ft_lstadd_back(&new, curr);
		lst = lst->next;
	}
	return (new);
}
