/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccraciun <ccraciun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/30 16:23:38 by ccraciun          #+#    #+#             */
/*   Updated: 2024/08/04 14:57:51 by ccraciun         ###   ########.fr       */
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
		write(2, "HOME not set\n", 14);
	if (dir && ft_strncmp(dir, "/", 1) == 0)
		new_path = ft_strdup(dir);
	else if (!dir || ft_strncmp(dir, "~", 1) == 0)
		new_path = ft_strdup(home);
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
	free(dir);
	return (update_pwd(cwd, my_envp), free(new_path), 0);
}
