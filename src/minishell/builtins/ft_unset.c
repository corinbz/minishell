/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccraciun <ccraciun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/30 16:23:38 by ccraciun          #+#    #+#             */
/*   Updated: 2024/07/01 13:32:06 by ccraciun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_unset(char *param, t_link_list **head)
{
	t_link_list	*curr;
	t_link_list	*prev;

	curr = *head;
	prev = NULL;
	while(curr)
	{
		if(ft_strncmp(param, curr->param, ft_strlen(param)) == 0)
		{
			if(prev)
				prev->next = curr->next;
			else
				*head = curr->next;
			free(curr);
			return(0);
		}
			prev = curr;
			curr = curr->next;
	}
	return(0);
}
