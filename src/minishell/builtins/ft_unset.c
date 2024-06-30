/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccraciun <ccraciun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/30 16:23:38 by ccraciun          #+#    #+#             */
/*   Updated: 2024/06/30 17:41:21 by ccraciun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_unset(char *param, t_link_list **head)
{
	t_link_list	*curr;
	t_link_list	*prev;
	t_link_list	*temp;

	curr = *head;
	prev = NULL;
	while(curr)
	{
		if(ft_strncmp(param, curr->param, ft_strlen(param)) == 0)
		{
			temp = curr;
			prev->next = curr->next;
			curr = prev->next;
			// free(temp);
			return(0);
		}
		if(curr->next)
		{
			prev = curr;
			curr = curr->next;
		}
		else
			return(0);
	}
	return(0);
}