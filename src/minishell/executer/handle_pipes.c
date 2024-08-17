/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_pipes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccraciun <ccraciun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 11:03:06 by corin             #+#    #+#             */
/*   Updated: 2024/08/17 10:55:39 by ccraciun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static pid_t	fork_and_exec_left(t_cmd *cmd, int end[2],
	char **envp, t_link_list *my_envp)
{
	pid_t	left;

	left = ft_fork();
	if (left == 0)
	{
		close(end[0]);
		if (dup2(end[1], STDOUT_FILENO) == -1)
			printf("dup2 left");
		close(end[1]);
		exec_cmd(((t_pipe_cmd *)cmd)->left, envp, &my_envp, true);
		exit(0);
	}
	return (left);
}

static pid_t	fork_and_exec_right(t_cmd *cmd, int end[2],
	char **envp, t_link_list *my_envp)
{
	pid_t	right;

	right = ft_fork();
	if (right == 0)
	{
		close(end[1]);
		if (dup2(end[0], STDIN_FILENO) == -1)
			printf("dup2 right");
		close(end[0]);
		exec_cmd(((t_pipe_cmd *)cmd)->right, envp, &my_envp, true);
		exit(0);
	}
	return (right);
}

int	exec_pipe(t_cmd *cmd, char **envp, t_link_list *my_envp)
{
	int		end[2];
	pid_t	left;
	pid_t	right;
	int		exitcode;

	if (pipe(end) < 0)
		ft_panic("pipe");
	left = fork_and_exec_left(cmd, end, envp, my_envp);
	right = fork_and_exec_right(cmd, end, envp, my_envp);
	close(end[0]);
	close(end[1]);
	waitpid(left, &exitcode, 0);
	waitpid(right, &exitcode, 0);
	exitcode = WEXITSTATUS(exitcode);
	return (exitcode);
}
