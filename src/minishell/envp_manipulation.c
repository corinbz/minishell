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


static t_link_list	*allocate_new_node(void)
{
	t_link_list	*new_node;

	new_node = ft_calloc(1, sizeof(*new_node));
	if (!new_node)
	{
		perror("calloc failed");
		return (NULL);
	}
	return (new_node);
}

static char	*duplicate_env_var(const char *env_var)
{
	char	*duplicate;

	duplicate = ft_strdup(env_var);
	if (!duplicate)
	{
		perror("strdup failed");
	}
	return (duplicate);
}

static void	append_node_to_list(t_link_list **head, t_link_list **current,
	t_link_list *new_node)
{
	if (!*head)
	{
		*head = new_node;
		*current = new_node;
	}
	else
	{
		(*current)->next = new_node;
		*current = new_node;
	}
}

t_link_list	*create_my_envp(char **envp)
{
	t_link_list	*head;
	t_link_list	*current;
	t_link_list	*new_node;
	int			i;

	i = 0;
	head = NULL;
	current = NULL;
	new_node = NULL;

	while (envp[i])
	{
		new_node = allocate_new_node();
		if (!new_node)
			return (NULL);
		new_node->param = duplicate_env_var(envp[i]);
		if (!new_node->param)
			return (free(new_node), NULL);
		append_node_to_list(&head, &current, new_node);
		i++;
	}
	return (head);
}
