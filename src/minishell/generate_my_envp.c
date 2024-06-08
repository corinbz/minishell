/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   generate_my_envp.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccraciun <ccraciun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 11:11:05 by ccraciun          #+#    #+#             */
/*   Updated: 2024/06/07 11:31:15by ccraciun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_envp(t_my_envp **envp)
{
	t_my_envp	*tmp;
	t_my_envp	*current;

	if (envp == NULL)
		return ;
	current = *envp;
	while (current)
	{
		tmp = current->next;
		free(current);
		current = tmp;
	}
	*envp = NULL;
}
t_my_envp	*create_my_envp(char **envp)
{
	t_my_envp *head;
	t_my_envp *current;
	t_my_envp *new_node;

	int i = 0;
	head = NULL;
	current = NULL;
	while (envp[i])
	{
		new_node = ft_calloc(1, sizeof(*new_node));
		if (!new_node)
			return(perror("calloc failed") ,NULL);
		new_node->param = envp[i];//free previously allocate new_node.param
		if (!new_node->param)
			return (perror("strdup failed"), free(new_node), NULL);
		if (!head)
		{
			head = new_node;
			current = new_node;
		}
		else
		{
			current->next = new_node;
			current = new_node;
		}
		i++;
	}
	return head;
}
t_my_envp	*get_last_value(t_my_envp *head)
{
	while(head->next)
	{
		head = head->next;
	}
	return(head);
}