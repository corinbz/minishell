/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccraciun <ccraciun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/30 16:23:38 by ccraciun          #+#    #+#             */
/*   Updated: 2024/07/06 14:07:58 by ccraciun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int update_oldpwd(char *newpwd, t_link_list *my_envp)
{
	char *joinedpwd;

	joinedpwd = ft_strjoin("OLDPWD=", newpwd);
	if(!joinedpwd)
		return(1);
	// printf("%s\n", joinedpwd);
	ft_export(joinedpwd, my_envp);
	free(joinedpwd);
	return(0);
}
static int update_pwd(char *newpwd, t_link_list *my_envp)
{
	char	*joinedpwd;

	joinedpwd = ft_strjoin("PWD=", newpwd);
	if(!joinedpwd)
		return(perror("strdup"),1);
	ft_export(joinedpwd, my_envp);
	free(joinedpwd);
	return(0);
}

int ft_cd(char *dir, t_link_list *my_envp)
{
	char			cwd[PATH_MAX];
	char			*new_path;
	char			*home;
	t_link_list 	*curr;

	getcwd(cwd,sizeof(cwd));
	curr = my_envp;
	update_oldpwd(cwd, my_envp);
	while(curr)
		{
			if(ft_strncmp(curr->param, "HOME=", 5) == 0)
				home = curr->param + 5;
			curr= curr->next;
		}
	if(!dir || ft_strncmp(dir,"~", 1) == 0)
		new_path = home;
	if(dir && ft_strncmp(dir,"~", 1) != 0)
	{
		dir = ft_strjoin("/", dir);
		if(!dir)
			return(perror("strjoin error\n"), 1);
		new_path = ft_strjoin(cwd,dir);
		if(!new_path)
			return(free(dir), 1);
	}
	if (chdir(new_path) == -1)
		return(perror("cd"), 1);
	getcwd(cwd,sizeof(cwd));
	update_pwd(cwd, my_envp);
	if(dir && ft_strncmp(dir,"~", 1) != 0)
		return(free(dir),free(new_path), 1);
	return (0);
}
