/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corin <corin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/30 16:23:38 by ccraciun          #+#    #+#             */
/*   Updated: 2024/07/30 11:52:54 by erybolov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_unset(char *param, t_link_list **head)
{
	t_link_list	*curr;
	t_link_list	*prev;

	if (!param)
		return (0);
	curr = *head;
	prev = NULL;
	while (curr)
	{
		if (ft_strncmp(param, curr->param, ft_strlen(param)) == 0)
		{
			if (prev)
				prev->next = curr->next;
			else
				*head = curr->next;
			free(curr);
			return (0);
		}
		prev = curr;
		curr = curr->next;
	}
	return (0);
}
