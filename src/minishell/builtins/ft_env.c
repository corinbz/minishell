/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccraciun <ccraciun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/30 16:23:38 by ccraciun          #+#    #+#             */
/*   Updated: 2024/08/10 11:48:15 by ccraciun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_env(t_link_list *head)
{
	t_link_list	*curr;

	curr = head;
	while (curr)
	{
		if ((ft_strncmp((char *)curr->param, "?=", 2) == 0))
		{
			curr = curr->next;
			continue ;
		}
		printf("%s\n", (char *)curr->param);
		curr = curr->next;
	}
	return (0);
}
