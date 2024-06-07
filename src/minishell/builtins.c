/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccraciun <ccraciun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 11:31:10 by ccraciun          #+#    #+#             */
/*   Updated: 2024/06/07 11:48:31 by ccraciun         ###   ########.fr       */
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

void	ft_env(t_my_envp *head)
{
	t_my_envp	*curr;
	
	curr = NULL;
	curr = head;
	while(curr)
	{
		printf("%s\n", curr->param);
		curr = curr->next;
	}
}

int	ft_echo(char *input, bool no_newline)
{
	if(no_newline)
	{
		printf("%s", input);
		return (0);
	}
	printf("%s\n", input);
	return(0);
}


void	ft_export(char *var_name, char *var_value, char **envp)
{
	
}