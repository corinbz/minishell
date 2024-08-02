/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corin <corin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/30 16:23:38 by ccraciun          #+#    #+#             */
/*   Updated: 2024/08/02 19:59:43 by corin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	update_oldpwd(char *newpwd, t_link_list *my_envp)
{
	char	*joinedpwd;

	joinedpwd = ft_strjoin("OLDPWD=", newpwd);
	if (!joinedpwd)
		return (1);
	ft_export(joinedpwd, my_envp);
	free(joinedpwd);
	return (0);
}

static int	update_pwd(char *newpwd, t_link_list *my_envp)
{
	char	*joinedpwd;

	joinedpwd = ft_strjoin("PWD=", newpwd);
	if (!joinedpwd)
		return (perror("strdup"), 1);
	ft_export(joinedpwd, my_envp);
	free(joinedpwd);
	return (0);
}

static int	ft_get_home(char **home, t_link_list *my_envp)
{
	t_link_list		*curr;

	curr = my_envp;
	while (curr)
	{
		if (ft_strncmp(curr->param, "HOME=", 5) == 0)
		{
			*home = curr->param + 5;
			return (0);
		}
		curr = curr->next;
	}
	return (1);
}

int	ft_cd(char *dir, t_link_list *my_envp)
{
	char	cwd[PATH_MAX];
	char	*new_path;
	char	*home;

	getcwd(cwd, sizeof(cwd));
	update_oldpwd(cwd, my_envp);
	if (ft_get_home(&home, my_envp))
		return (perror("HOME not set\n"), 1);
	else if (!dir || ft_strncmp(dir, "~", 1) == 0)
		new_path = ft_strdup(home);
	else if (ft_strncmp(dir, "/", 1) == 0)
		new_path = ft_strdup(dir);
	else
	{
		dir = ft_strjoin("/", dir);
		if (!dir)
			return (perror("strjoin error\n"), 1);
		new_path = ft_strjoin(cwd, dir);
		if (!new_path)
			return (free(dir), 1);
	}
	if (chdir(new_path) == -1)
		return (free(dir), free(new_path), perror("cd"), 1);
	return (update_pwd(cwd, my_envp), free(new_path), 0);
}
