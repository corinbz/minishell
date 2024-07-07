/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_paths.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccraciun <ccraciun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 15:09:11 by ccraciun          #+#    #+#             */
/*   Updated: 2024/07/01 14:07:11 by ccraciun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	executable_exists(char *path)
{
	if (access(path, X_OK) != -1)
		return (true);
	return (false);
}
char **get_possible_paths(char **envp)
{
	char	**possible_paths;
	int		i;

	i = 0;
	if(envp)
	{
		while (envp[i])
		{
			if(!ft_strncmp("PATH", envp[i], 4))
			{
				possible_paths = ft_split(envp[i] + 5, ':');
				if(!possible_paths)
					return(ft_panic("possible paths malloc failed\n"), NULL);
				return(possible_paths);
			}
			i++;
		}
	}
	return (NULL);
}
char *get_path(char *cmd, char **paths)
{
	int		i;
	char	*full_path;

	i = 0;
	cmd = ft_strjoin("/", cmd);
	if (!cmd)
		return (printf("cmd alloc fail\n"), NULL);
	if(!paths)
		return(cmd);
	while(paths[i])
	{
		full_path = ft_strjoin(paths[i], cmd);
		if(!full_path)
			return(free(cmd), NULL);
		if(executable_exists(full_path))
			return(free(cmd), full_path);
		free(full_path);
		i++;
	}
	free(cmd);
	return (full_path);
}
