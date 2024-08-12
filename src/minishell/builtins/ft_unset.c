/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corin <corin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/30 16:23:38 by ccraciun          #+#    #+#             */
/*   Updated: 2024/08/12 18:44:36 by corin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
 * Compares an environment variable name with a full environment variable string.
 * @param param The variable name to search for.
 * @param env_var The full environment variable string (e.g., "VAR=value").
 * @return 1 if the names match, 0 otherwise.
 */
static int	compare_env_var(const char *param, const char *env_var)
{
	char	*equals_sign;
	size_t	name_length;

	equals_sign = strchr(env_var, '=');
	if (equals_sign)
	{
		name_length = equals_sign - env_var;
		return (ft_strncmp(param, env_var, name_length)
			== 0 && param[name_length] == '\0');
	}
	return (0);
}

/*
 * Removes a node from the linked list and frees associated memory.
 * @param head Pointer to the head of the list.
 * @param prev The previous node in the list (NULL if removing the head).
 * @param curr The node to remove.
 */
static void	remove_node(t_link_list **head,
		t_link_list *prev, t_link_list *curr)
{
	if (prev)
		prev->next = curr->next;
	else
		*head = curr->next;
	free(curr->param);
	curr->param = NULL;
	free(curr);
	curr = NULL;
}

/*
 * Searches for an environment variable in the list and removes it if found.
 * @param param The name of the environment variable to remove.
 * @param head Pointer to the head of the list.
 * @return 1 if the variable was found and removed, 0 otherwise.
 */
static int	find_and_remove_var(char *param, t_link_list **head)
{
	t_link_list	*curr;
	t_link_list	*prev;

	curr = *head;
	prev = NULL;
	while (curr)
	{
		if (compare_env_var(param, curr->param))
		{
			remove_node(head, prev, curr);
			return (0);
		}
		prev = curr;
		curr = curr->next;
	}
	return (0);
}

/*
 * Removes an environment variable from the list.
 * @param param The name of the environment variable to unset.
 * @param head Pointer to the head of the environment variable list.
 * @return 1 if the variable was found and removed, 0 otherwise.
 */
int	ft_unset(char *param, t_link_list **head)
{
	int	res;

	res = 0;
	if (!param || !head || !*head)
		return (res);
	res = find_and_remove_var(param, head);
	return (res);
}
