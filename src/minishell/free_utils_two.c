/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils_two.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corin <corin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 12:12:48 by corin             #+#    #+#             */
/*   Updated: 2024/07/31 20:14:20 by corin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_envp(t_link_list **envp)
{
	t_link_list	*tmp;
	t_link_list	*current;

	if (envp == NULL || *envp == NULL)
		return ;
	current = *envp;
	while (current)
	{
		tmp = current->next;
		free(current->param);
		free(current);
		current = tmp;
	}
	*envp = NULL;
}
