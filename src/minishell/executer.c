/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccraciun <ccraciun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 16:51:21 by ccraciun          #+#    #+#             */
/*   Updated: 2024/07/15 13:28:05 by ccraciun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


int	exec_exec(t_cmd *cmd, char **envp, t_link_list *my_envp, bool is_child)
{
	char		**paths;
	char		*cmd_path;
	t_exec_cmd	*type_exec_cmd;
	t_link_list	*builtins;
	int			exitcode;
	
	type_exec_cmd = (t_exec_cmd*)cmd;
	// printf("executing %s\n",type_exec_cmd->arg_start[0]);
	// printf("builtin type is %d\n",builtin_type(type_exec_cmd));
	if(builtin_type(type_exec_cmd) == 1)
	{
		exitcode = run_builtin_parent(type_exec_cmd, my_envp);
		free(cmd);
		if(is_child)
			ft_exit(NULL,exitcode);
		return(exitcode);
	}
	if(builtin_type(type_exec_cmd) == 2)
	{
		// if(ft_strncmp(type_exec_cmd->arg_start[0], "echo", 4) == 0)
		// 	return(ft_echo(type_exec_cmd->arg_start[1], type_exec_cmd->arg_start));
		exitcode = run_builtin_child(type_exec_cmd, my_envp);
		if(is_child)
		{
			// printf("got here\n");
			exit(exitcode);
		}
		free(cmd);
		return(exitcode);
	}
	envp = link_list_to_array(&my_envp);
	paths = get_possible_paths(envp);
	cmd_path = get_path(type_exec_cmd->arg_start[0], paths);
	if(!is_child)
	{
		int pid = ft_fork();
		// run_signals(1);
		if (pid == 0)
		{
			if(execve(cmd_path, type_exec_cmd->arg_start, envp) == -1)
				{
				printf("%s: no executable found\n", type_exec_cmd->arg_start[0]);
				ft_free_2d(envp);
				ft_exit("127",g_signal);
				}
		}
		waitpid(pid, &exitcode, 0);
		// ft_free_2d(envp);
		return(exitcode);
	}
	if(execve(cmd_path, type_exec_cmd->arg_start, envp) == -1)
		{
		printf("%s: no executable found\n", type_exec_cmd->arg_start[0]);
		ft_free_2d(envp);
		ft_exit("127", g_signal);
		}
	exit(0);
}

int exec_redir(t_cmd *cmd, char **envp, t_link_list *my_envp)
{
	t_redir_cmd	*type_redir_cmd;
	int			new_fd;
	int			original_fd;
	char		*error;

	type_redir_cmd = (t_redir_cmd*)cmd;
	// close(type_redir_cmd->fd);
	// if(type_redir_cmd->heredoc)
	// {
	// 	char *eof = "eof";
	// 	ft_heredoc(eof, envp);
	// }
	new_fd = open(type_redir_cmd->token_start_pos, type_redir_cmd->mode, DEFAULT_CHMOD);
	if(new_fd < 0)
	{
		error = "failed to create file\n";
		ft_putstr_fd(error,2);
		return(1);
	}
	if (dup2(new_fd, type_redir_cmd->fd) == -1)
	{
		error = "dup2 failed\n";
		ft_putstr_fd(error, 2);
		close(new_fd);
		return(1);
	}
	close(new_fd);
	exec_cmd(type_redir_cmd->sub_cmd, envp, my_envp, false);
	original_fd = open("/dev/tty", O_WRONLY);
	dup2(original_fd, type_redir_cmd->fd);
	close(original_fd);
	return (0);
}

int exec_pipe(t_cmd *cmd, char **envp, t_link_list *my_envp)
{
	int			end[2];
	int			status;
	pid_t		left;
	pid_t		right;
	t_pipe_cmd	*type_pipe_cmd;

	type_pipe_cmd = (t_pipe_cmd *) cmd;
	if(pipe(end) < 0)
		ft_panic("pipe");
	left = ft_fork();
	if(left == 0)
	{
		close(end[0]);
		if (dup2(end[1], STDOUT_FILENO) == -1)
			ft_panic("dup2 left");
		close(end[1]);
		exec_cmd(type_pipe_cmd->left, envp, my_envp, true);
		exit(1);
	}
	right = ft_fork();
	if(right == 0)
	{
		close(end[1]);
		if (dup2(end[0], STDIN_FILENO) == -1)
			ft_panic("dup2 right");
		close(end[0]);
		exec_cmd(type_pipe_cmd->right, envp, my_envp, true);
		exit(1);
	}
	if(right == 0)
		exit(status);
	close(end[0]);
	close(end[1]);
	waitpid(left, &status, 0);
	waitpid(right, &status, 0);
	return(status);
}
int exec_cmd(t_cmd *cmd, char **envp, t_link_list *my_envp, bool is_child)
{
	int	exitcode;
	if (cmd->type == EXEC)
		exitcode = exec_exec(cmd, envp, my_envp, is_child);
	if(cmd->type == REDIR)
		exitcode = exec_redir(cmd, envp, my_envp);
	if(cmd->type == PIPE)
		exitcode = exec_pipe(cmd, envp, my_envp);
	// printf("%d\n", exitcode);
	return(exitcode);
}