/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corin <corin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 15:00:23 by corin             #+#    #+#             */
/*   Updated: 2024/07/20 15:00:56 by corin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int copy_file_to_fd(const char *src_path, int dest_fd) {
	int src_fd;
	ssize_t bytes_read, bytes_written;
	char buffer[BUFSIZ];

	src_fd = open(src_path, O_RDONLY);
	if (src_fd < 0) {
		perror("Error opening source file");
		return -1;
	}

	while ((bytes_read = read(src_fd, buffer, sizeof(buffer))) > 0) {
		bytes_written = write(dest_fd, buffer, bytes_read);
		if (bytes_written != bytes_read) {
			perror("Error writing to destination file descriptor");
			close(src_fd);
			return -1;
		}
	}

	if (bytes_read < 0) {
		perror("Error reading from source file");
		close(src_fd);
		return -1;
	}

	close(src_fd);
	return 0;
}

int exec_heredoc(t_cmd *cmd, char **envp, t_link_list *my_envp, bool is_child) {
	char *input;
	char *input_newline;
	t_heredoc_cmd *heredoc;
	char *new_eof;
	int original_stdin;
	int exitcode;

	heredoc = (t_heredoc_cmd *)cmd;
	new_eof = ft_substr(heredoc->eof_start, 0, ft_strlen(heredoc->eof_start) - ft_strlen(heredoc->eof_end));
	heredoc->temp_fd = open("heredoc", O_CREAT | O_RDWR | O_TRUNC, DEFAULT_CHMOD);
	original_stdin = dup(STDIN_FILENO);
	if (heredoc->temp_fd < 0) {
		perror("Error opening heredoc file");
		return 1;
	}

	while (1) {
		input = readline("heredoc> ");
		if (!input) {
			close(heredoc->temp_fd);
			unlink("heredoc");
			exit(1);
		}
		if (ft_strncmp(input, new_eof, ft_strlen(new_eof)) == 0) {
			free(input);
			close(heredoc->temp_fd);
			// Redirect STDIN from the heredoc file
			int new_fd = open("heredoc", O_RDONLY);
			if (new_fd < 0) {
				perror("Error reopening heredoc file");
				return 1;
			}
			if (dup2(new_fd, STDIN_FILENO) < 0) {
				perror("Error redirecting STDIN");
				close(new_fd);
				return 1;
			}
			close(new_fd);
			unlink("heredoc");
			exitcode = exec_cmd(heredoc->sub_cmd, envp, my_envp, false);
			dup2(original_stdin, STDIN_FILENO);
			close(original_stdin);
			free(new_eof);
			return (exitcode);
		} else {
			input_newline = ft_strjoin(input, "\n");
			if (!input_newline) {
				free(input);
				return 1;
			}
			expand_dollar_signs(input_newline, my_envp);
			ft_putstr_fd(input_newline, heredoc->temp_fd);
			free(input_newline);
		}
		free(input);
	}
}
