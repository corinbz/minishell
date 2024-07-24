/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_pipes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corin <corin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 11:03:06 by corin             #+#    #+#             */
/*   Updated: 2024/07/20 11:03:48 by corin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int exec_pipe(t_cmd *cmd, char **envp, t_link_list *my_envp)
{
	int end[2];
	if (pipe(end) < 0)
		ft_panic("pipe");

	pid_t left = ft_fork();
	if (left == 0)
	{
		close(end[0]);
		if (dup2(end[1], STDOUT_FILENO) == -1)
			ft_panic("dup2 left");
		close(end[1]);
		exec_cmd(((t_pipe_cmd *)cmd)->left, envp, my_envp, true);
		exit(1);
	}

	pid_t right = ft_fork();
	if (right == 0)
	{
		close(end[1]);
		if (dup2(end[0], STDIN_FILENO) == -1)
			ft_panic("dup2 right");
		close(end[0]);
		exec_cmd(((t_pipe_cmd *)cmd)->right, envp, my_envp, true);
		exit(1);
	}

	close(end[0]);
	close(end[1]);
	int status;
	waitpid(left, &status, 0);
	waitpid(right, &status, 0);
	return status;
}