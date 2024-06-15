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
			free(temp);
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
void	free_envp(t_link_list **envp)
{
	t_link_list	*tmp;
	t_link_list	*current;

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
t_link_list	*create_my_envp(char **envp)
{
	t_link_list *head;
	t_link_list *current;
	t_link_list *new_node;

	int i = 0;
	head = NULL;
	current = NULL;
	new_node = NULL;
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
t_link_list	*get_last_value(t_link_list *head)
{
	while(head->next)
		head = head->next;
	return(head);
}