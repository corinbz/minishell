/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corin <corin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 12:55:03 by corin             #+#    #+#             */
/*   Updated: 2024/07/28 12:56:10 by corin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	restore_original_fds(int original_stdout_fd, int original_stdin_fd)
{
	if (dup2(original_stdout_fd, STDOUT_FILENO) == -1
		|| dup2(original_stdin_fd, STDIN_FILENO) == -1)
	{
		perror("dup2 failed to restore");
		close(original_stdout_fd);
		close(original_stdin_fd);
		return (1);
	}
	close(original_stdout_fd);
	close(original_stdin_fd);
	return (0);
}

int	save_original_fds(int *original_stdout_fd, int *original_stdin_fd)
{
	*original_stdout_fd = dup(STDOUT_FILENO);
	*original_stdin_fd = dup(STDIN_FILENO);
	if (*original_stdout_fd == -1 || *original_stdin_fd == -1)
	{
		perror("dup failed");
		return (1);
	}
	return (0);
}
