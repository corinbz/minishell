/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccraciun <ccraciun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 12:51:03 by ccraciun          #+#    #+#             */
/*   Updated: 2024/08/10 12:52:05 by ccraciun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	change_directory(char *new_path, t_link_list *my_envp)
{
	char	cwd[PATH_MAX];

	if (chdir(new_path) == -1)
	{
		perror("cd");
		free(new_path);
		return (1);
	}
	getcwd(cwd, sizeof(cwd));
	update_pwd(cwd, my_envp);
	free(new_path);
	return (0);
}

char	*get_new_path(char *dir, char *home, char *cwd)
{
	char	*new_path;

	if (dir && ft_strncmp(dir, "/", 1) == 0)
		new_path = ft_strdup(dir);
	else if (!dir || ft_strncmp(dir, "~", 1) == 0)
		new_path = ft_strdup(home);
	else
	{
		dir = ft_strjoin("/", dir);
		if (!dir)
			return (NULL);
		new_path = ft_strjoin(cwd, dir);
		free(dir);
		if (!new_path)
			return (NULL);
	}
	return (new_path);
}
