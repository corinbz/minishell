/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corin <corin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 17:35:00 by erybolov          #+#    #+#             */
/*   Updated: 2024/05/27 10:48:524:42 by corin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec_exec(t_cmd *cmd, char **envp)
{
	char		**paths;
	char		*cmd_path;
	t_exec_cmd	*type_exec_cmd;

	paths = get_possible_paths(envp);
	type_exec_cmd = (t_exec_cmd*)cmd;
	cmd_path = get_path(type_exec_cmd->arg_start[0], paths);
	if(execve(cmd_path, type_exec_cmd->arg_start, envp) == -1)
		{
		printf(2, "execve failed on %s\n", type_exec_cmd->arg_start[0]);
		return(1);
		}
	return(0);
}

int exec_redir(t_cmd *cmd, char **envp)
{
	t_redir_cmd	*type_redir_cmd;

	type_redir_cmd = (t_redir_cmd*)cmd;
	close(type_redir_cmd->fd);
	if(open(type_redir_cmd->token_start_pos, type_redir_cmd->mode) < 0)
	{
		printf(2, "failed to open %s\n", type_redir_cmd->token_start_pos);
		return(1);
	}
	exec_cmd(type_redir_cmd->sub_cmd, envp);
	return (0);
}

int exec_pipe(t_cmd *cmd, char **envp)
{
	t_pipe_cmd	*type_pipe_cmd;
	int			end[2];
	pid_t		left;
	pid_t		right;
	int			status;

	type_pipe_cmd = (t_pipe_cmd*)cmd;
	if(pipe(end) < 0)
		panic("pipe");
	left = ft_fork();
	if(left == 0)
	{
		close(end[0]);
		dup2(end[1], STDOUT_FILENO);
		close(end[1]);
		exec_cmd(type_pipe_cmd->left, envp);
	}

	right = ft_fork();
	if(right == 0)
	{
		close(end[1]);
		dup2(end[0], STDIN_FILENO);
		close(end[0]);
		exec_cmd(type_pipe_cmd->right, envp);
	}
	waitpid(left, &status, 0);
	waitpid(right, &status, 0);
	return(0);
}
int exec_cmd(t_cmd *cmd, char **envp)
{

	if (cmd == EXEC)
		exec_exec(cmd, envp);
	if(cmd == REDIR)
		exec_redir(cmd, envp);
	if(cmd == PIPE)
	{
	}
}
int main(int argc, char **argv, char **envp)
{
	if (argc != 1 || argv[1])
	{
		ft_panic("This program does not accept arguments\n");
		exit(0);
	}
	return (EXIT_SUCCESS);
}

/* m as variable name because later we would like to work with nested structs like m->some->struct->another
 * m is static so we don't have to set fields as NULL
 *
 * minishell_run is a program loop that will interact with user
 *
 * also we have to implement cleanup (free etc) before we exit from main
 */