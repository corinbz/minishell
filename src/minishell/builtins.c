/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccraciun <ccraciun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 11:31:10 by ccraciun          #+#    #+#             */
/*   Updated: 2024/06/08 16:19:49by ccraciun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
/*
done:
pwd with no options
env with no options or arguments

todo:
echo with option -n
cd with only a relative or absolute path
export with no options
unset with no options
exit with no options
*/

void	ft_pwd()
{
	char *buff;
	
	buff = getcwd(NULL, 0);
	if (buff)
	{
		printf("%s\n", buff);
		free(buff);
	}
	else
	{
		printf("getcwd error\n");
	}
}

void	ft_env(t_link_list *head)
{
	while(head)
	{
		printf("%s\n", head->param);
		head = head->next;
	}
}

int	ft_echo(char *newline, char *input)
{
	if(ft_strncmp(newline, "-n", 2) == 0)
	{
		printf("%s", input);
		return (0);
	}
	printf("%s\n", newline);
	return(0);
}


int	ft_export(char *new_param, t_link_list *head)
{
	t_link_list	*temp;
	t_link_list	*last;
	
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
