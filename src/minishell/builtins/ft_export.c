/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corin <corin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/30 15:34:05 by ccraciun          #+#    #+#             */
/*   Updated: 2024/08/06 21:11:13 by corin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	param_valid(char *param)
{
	int	i;

	i = 0;
	if (ft_strchr(param, '=') == NULL)
		return (0);
	while (param[i] != '=' && param[i])
	{
		if (ft_isalpha(param[i]) || param[i] == '?')
			return (1);
		i++;
	}
	return (0);
}

static int	change_if_exists(char *new_param, t_link_list *head)
{
	int			param_len;
	t_link_list	*curr;

	curr = head;
	param_len = 0;
	while (new_param[param_len] != '=' && new_param[param_len] != '\0')
	{
		param_len++;
	}
	while (curr && curr->param)
	{
		if (ft_strncmp(curr->param, new_param, param_len) == 0)
		{
			free(curr->param);
			curr->param = ft_strdup(new_param);
			if (!curr->param)
			{
				perror("strdup");
				exit(1);
			}
			return (1);
		}
		curr = curr->next;
	}
	return (0);
}

static int	add_new_param(char *new_param, t_link_list *head)
{
	t_link_list	*temp;
	t_link_list	*last;

	temp = ft_calloc(1, sizeof(*temp));
	if (temp == NULL)
		return (1);
	temp->param = ft_strdup(new_param);
	if (!temp->param)
	{
		perror("strdup");
		free(temp);
		return (1);
	}
	if (!head->param)
	{
		head->param = temp->param;
		free(temp);
		return (0);
	}
	last = get_last_value(head);
	last->next = temp;
	temp->next = NULL;
	return (0);
}

int	ft_export(char *new_param, t_link_list *head)
{
	if (!new_param)
	{
		while (head)
		{
			printf("declare -x %s", (char *)head->param);
			head = head->next;
		}
		return (0);
	}
	if (!param_valid(new_param))
		return (0);
	if (change_if_exists(new_param, head))
		return (0);
	return (add_new_param(new_param, head));
}
