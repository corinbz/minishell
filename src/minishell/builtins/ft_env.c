/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corin <corin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/30 16:23:38 by ccraciun          #+#    #+#             */
/*   Updated: 2024/08/06 19:25:45 by corin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_env(t_link_list *head)
{
	t_link_list	*curr;

	curr = head;
	while (curr)
	{
		printf("%s\n", (char *)curr->param);
		curr = curr->next;
	}
	return (0);
}
