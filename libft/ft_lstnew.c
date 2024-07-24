/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erybolov <erybolov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 04:07:15 by erybolov          #+#    #+#             */
/*   Updated: 2024/07/24 18:20:57 by erybolov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_link_list	*ft_lstnew(void *content)
{
	t_link_list	*node;

	node = malloc(sizeof(t_link_list));
	if (node == NULL)
		return (NULL);
	node->param = content;
	node->next = NULL;
	return (node);
}
