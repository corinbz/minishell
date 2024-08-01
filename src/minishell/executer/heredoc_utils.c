/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corin <corin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 14:28:54 by corin             #+#    #+#             */
/*   Updated: 2024/08/01 19:08:45 by corin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*create_new_eof(const char *eof_start, const char *eof_end)
{
	return (ft_substr(eof_start, 0, ft_strlen(eof_start) - ft_strlen(eof_end)));
}

int	copy_file_to_fd(const char *src_path, int dest_fd)
{
	int		src_fd;
	ssize_t	bytes_read;
	ssize_t	bytes_written;
	char	buffer[BUFSIZ];

	src_fd = open(src_path, O_RDONLY);
	if (src_fd < 0)
		return (perror("Error opening source file"), -1);
	while (bytes_read > 0)
	{
		bytes_read = read(src_fd, buffer, sizeof(buffer));
		bytes_written = write(dest_fd, buffer, bytes_read);
		if (bytes_written != bytes_read)
			return (perror("Error writing to destination file descriptor"),
				close(src_fd), -1);
	}
	if (bytes_read < 0)
	{
		perror("Error reading from source file");
		close(src_fd);
		return (-1);
	}
	close(src_fd);
	return (0);
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
