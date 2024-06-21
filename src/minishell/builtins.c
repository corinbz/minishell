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

int	ft_echo(char *newline, char **input)
{
	int i;

	i = 1;
	if(ft_strncmp(newline, "-n", 2) == 0)
	{
		while(newline[i] == 'n')
			{
				i++;
				if (newline[i] != 'n' && newline[i] != '\0')
				{
					i = 1;
					printf("%s ",newline);
					while(input[++i])
						printf("%s\n",input[i]);
					return (0);
				}
			}
		i = 2;
		while(input[i])
		{
			printf("%s", input[i]);
			i++;
			if(input[i])
				printf(" ");
		}
		return (0);
	}
	// i = 1;
	while(input[i])
	{
		printf("%s", input[i]);
		i++;
		if(input[i])
			printf(" ");
	}
	printf("\n");
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
void ft_cd(char *dir, t_link_list *my_envp)
{
	char		cwd[PATH_MAX];
	char		*new_path;
	char		*home;

	getcwd(cwd,sizeof(cwd));
	while(my_envp)
		{
			if(ft_strncmp(my_envp->param, "HOME=", 5) == 0)
				home = my_envp->param + 5;
			my_envp= my_envp->next;
		}
	if(!dir)
		new_path = home;
	if(dir)
	{
		dir = ft_strjoin("/", dir);//protect
		if(!dir)
			return(perror("strjoin error\n"));
		new_path = ft_strjoin(cwd,dir);
		if(!new_path)
			return(free(dir));
	}
	if (chdir(new_path) == -1)
		return(perror("cd"));
	if(dir)
		return(free(dir),free(new_path));
}

int ft_exit(char **args, int last_status)
{
	int exit_status = last_status;

	if (args[1] != NULL) 
	{
		exit_status = ft_atoi(args[1]);
	}

	exit(exit_status);
}