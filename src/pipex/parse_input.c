/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corin <corin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 18:46:25 by ccraciun          #+#    #+#             */
/*   Updated: 2024/03/08 20:48:22 by corin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	get_possible_paths(t_data *data, char **envp)
{
	char	*tmp;
	size_t	i;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp("PATH", envp[i], 4) == 0)
		{
			free_2d(data->possible_paths);
			data->possible_paths = ft_split(envp[i], ':');
			if (!data->possible_paths)
				display_error(data, "Malloc failed in get_possible_paths");
			tmp = ft_substr(data->possible_paths[0], 5,
					ft_strlen(data->possible_paths[0]) - 5);
			if (!tmp)
				display_error(data,
					"Malloc failed in get_possible_paths");
			free(data->possible_paths[0]);
			data->possible_paths[0] = tmp;
			return ;
		}
		i++;
	}
	display_error(data, "PATH not found in envp\n");
}

bool	executable_exists(char *path)
{
	if (access(path, X_OK) != -1)
		return (true);
	return (false);
}

size_t	ft_2dstrlen(char **arr)
{
	size_t	i;

	i = 0;
	while (arr[i])
		i++;
	return (i);
}

void	get_cmd_path(t_data *data, size_t cmd_nr)
{
	size_t	i;
	char	*new_cmd;
	size_t	path_len;

	i = 0;
	path_len = ft_2dstrlen(data->possible_paths);
	new_cmd = ft_strjoin("/", data->cmd_args[cmd_nr][0]);
	if (!new_cmd)
		display_error(data, "Malloc failed in get_cmd_path");
	while (i < path_len)
	{
		data->cmd_paths[cmd_nr] = ft_strjoin(data->possible_paths[i],
				new_cmd);
		if (!data->cmd_paths[cmd_nr])
			return (free(new_cmd), display_error(data,
					"Malloc failed in get_cmd_path"));
		if (executable_exists(data->cmd_paths[cmd_nr]))
			return (free(new_cmd));
		i++;
		if (i < path_len)
			free(data->cmd_paths[cmd_nr]);
	}
	free(new_cmd);
}

void	get_cmd_incl_flags(t_data *data, char *raw_cmd, size_t cmd_nr)
{
	data->cmd_args[cmd_nr] = ft_split(raw_cmd, ' ');
	if (!data->cmd_args[cmd_nr])
		display_error(data, "Malloc failed in get_cmd_incl_flags");
}
