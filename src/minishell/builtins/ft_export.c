/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccraciun <ccraciun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/30 15:34:05 by ccraciun          #+#    #+#             */
/*   Updated: 2024/07/01 12:55:06 by ccraciun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int change_if_exists(char *new_param, t_link_list *head)
{
	int param_len;
	t_link_list *curr;

	curr = head;
	param_len = 0;
	while (new_param[param_len] != '=' && new_param[param_len] != '\0')
	{
		param_len++;
	}
	while(curr)
	{
		if(ft_strncmp(curr->param,new_param,5) == 0)
		{
			free(curr->param);
			curr->param = ft_strdup(new_param);
			if (!curr->param)
			{
				perror("strdup");
				exit(1);
			}
			return(1);
		}
		curr = curr->next;
	}
	return(0);
}

/*
returns 0 on succes, 1 on failure
*/
int	ft_export(char *new_param, t_link_list *head)
{
	t_link_list	*temp;
	t_link_list	*last;
	t_link_list	*curr;
	
	curr = head;
	if(!new_param)
		{
			while(head)
			{
				printf("declare -x %s", head->param);
				head = head->next;
			}
			return(0);
		}
	if (change_if_exists(new_param, head))
		return(0);
	temp = (t_link_list*)ft_calloc(1, sizeof(*temp));
	if (temp == NULL)
		return (1);
	temp->param = ft_strdup(new_param);
	if (!temp->param)
	{
		perror("strdup");
		free(temp);
		return 1;
	}
	if(!head->param)
	{
		head->param = temp->param;
		free(temp);
		return(0);
	}
	last = get_last_value(head);
	last->next = temp;
	return(0);
}
