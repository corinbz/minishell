/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccraciun <ccraciun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/30 16:23:38 by ccraciun          #+#    #+#             */
/*   Updated: 2024/06/30 16:28:18 by ccraciun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int ft_cd(char *dir, t_link_list *my_envp)
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
			return(perror("strjoin error\n"), 1);
		new_path = ft_strjoin(cwd,dir);
		if(!new_path)
			return(free(dir), 1);
	}
	if (chdir(new_path) == -1)
		return(perror("cd"), 1);
	if(dir)
		return(free(dir),free(new_path), 1);
	return (0);
}