/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccraciun <ccraciun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 14:28:54 by corin             #+#    #+#             */
/*   Updated: 2024/08/04 13:03:31 by erybolov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*create_new_eof(const char *eof_start, const char *eof_end)
{
	return (ft_substr(eof_start, 0, ft_strlen(eof_start) - ft_strlen(eof_end)));
}

int	duplicate_stdin(int *original_stdin)
{
	*original_stdin = dup(STDIN_FILENO);
	if (*original_stdin == -1)
	{
		perror("Error duplicating STDIN");
		return (1);
	}
	return (0);
}

int	close_temp_fd_and_unlink(int temp_fd, const char *file)
{
	close(temp_fd);
	unlink(file);
	return (0);
}

// Open and initialize the heredoc file
int	open_heredoc_file(int *temp_fd)
{
	*temp_fd = open("heredoc", O_CREAT | O_RDWR | O_TRUNC, DEFAULT_CHMOD);
	if (*temp_fd < 0)
	{
		perror("Error opening heredoc file");
		return (1);
	}
	return (0);
}
