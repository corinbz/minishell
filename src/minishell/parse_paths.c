/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_paths.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corin <corin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 15:09:11 by ccraciun          #+#    #+#             */
/*   Updated: 2024/08/02 04:56:33 by erybolov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	executable_exists(char *path)
{
	DIR	*dir;

	dir = opendir(path);
	if (dir != NULL)
	{
		closedir(dir);
		return (3);
	}
	if (access(path, F_OK) == 0)
	{
		if (access(path, X_OK) == 0)
			return (1);
		return (2);
	}
	return (0);
}

static char	*check_path(char *path, char *full_cmd)
{
	char	*full_path;
	int		exists;

	full_path = ft_strjoin(path, full_cmd);
	if (!full_path)
		return (NULL);
	exists = executable_exists(full_path);
	if (exists == 1)
		return (full_path);
	else if (exists == 2)
	{
		free(full_path);
		return (ft_strdup("Permission denied"));
	}
	free(full_path);
	return (NULL);
}

static char	*search_paths(char **paths, char *full_cmd)
{
	int		i;
	char	*result;

	i = 0;
	while (paths[i])
	{
		result = check_path(paths[i], full_cmd);
		if (result)
			return (result);
		i++;
	}
	return (ft_strdup("no valid path found"));
}

char	**get_possible_paths(char **envp)
{
	char	**possible_paths;
	int		i;

	i = 0;
	if (envp)
	{
		while (envp[i])
		{
			if (!ft_strncmp("PATH", envp[i], 4))
			{
				possible_paths = ft_split(envp[i] + 5, ':');
				if (!possible_paths)
					return (ft_panic("possible paths malloc failed\n"), NULL);
				return (possible_paths);
			}
			i++;
		}
	}
	return (NULL);
}

char	*get_path(char *cmd, char **paths)
{
	char	*result;
	char	*full_cmd;
	int		exists;

	if (ft_strchr(cmd, '/') != 0)
	{
		exists = executable_exists(cmd);
		if (exists == 2)
			return (ft_strdup("Permission denied"));
		else if (exists == 3)
			return (ft_strdup("Is a directory"));
		return (ft_strdup(cmd));
	}
	full_cmd = ft_strjoin("/", cmd);
	if (!full_cmd)
		return (printf("cmd alloc fail\n"), NULL);
	if (!paths)
		return (free(full_cmd), ft_strdup(cmd));
	result = search_paths(paths, full_cmd);
	free(full_cmd);
	return (result);
}
