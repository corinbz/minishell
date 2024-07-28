/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corin <corin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 04:07:15 by erybolov          #+#    #+#             */
/*   Updated: 2024/07/28 11:21:29 by corin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_link_list	*ft_lstmap(t_link_list *lst, void *(*f)(void *),
						void (*del)(void *))
{
	t_link_list	*new_lst;
	t_link_list	*node;

	new_lst = NULL;
	while (lst != NULL)
	{
		node = ft_lstnew(NULL);
		if (node == NULL)
		{
			ft_lstclear(&new_lst, del);
			return (NULL);
		}
		node->param = f(lst->param);
		ft_lstadd_back(&new_lst, node);
		lst = lst->next;
	}
	return (new_lst);
}
