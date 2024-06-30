/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccraciun <ccraciun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/30 15:34:05 by ccraciun          #+#    #+#             */
/*   Updated: 2024/06/30 16:00:50 by ccraciun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int change_if_exists(char *new_param, t_link_list *head)
{
	int param_len;
	int i;
	t_link_list *curr;

	curr = head;
	param_len = 0;
	i = 0;
	while(new_param[i] != '=')
	{
		param_len++;
		i++;
	}
	while(curr)
	{
		if(ft_strncmp(curr->param,new_param,5) == 0)
		{
			curr->param = new_param;
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
				printf("declare -x ");
				printf("%s\n", head->param);
				head = head->next;
			}
			return(0);
		}
	if (change_if_exists(new_param, head))
		return(0);
	temp = (t_link_list*)ft_calloc(1, sizeof(*temp));
	if (temp == NULL)
		return (1);
	temp->param = new_param;
	if(!head->param)
	{
		head->param = new_param;
		return(0);
	}
	last = get_last_value(head);
	last->next = temp;
	return(0);
}
