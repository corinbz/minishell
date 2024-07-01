/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccraciun <ccraciun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 16:51:21 by ccraciun          #+#    #+#             */
/*   Updated: 2024/07/01 14:09:25 by ccraciun         ###   ########.fr       */
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
	if(builtin_type(type_exec_cmd) == 1)
	{
		// printf("gothere\n");
		exitcode = run_builtin_parent(type_exec_cmd, my_envp);
		free(cmd);
		if(is_child)
			exit(exitcode);
		return(exitcode);
	}
	if(builtin_type(type_exec_cmd) == 2)
	{
		exitcode = run_builtin_child(type_exec_cmd, my_envp);
		free(cmd);
		if(is_child)
			exit(exitcode);
		return(exitcode);
	}
	envp = link_list_to_array(&my_envp);
	paths = get_possible_paths(envp);
	cmd_path = get_path(type_exec_cmd->arg_start[0], paths);
	if(!is_child)
	{
		int pid = ft_fork();
		if (pid == 0)
		{
			if(execve(cmd_path, type_exec_cmd->arg_start, envp) == -1)
				{
				printf("%s: no executable found\n", type_exec_cmd->arg_start[0]);
				return(ft_free_2d(envp),1);
				}
		}
		waitpid(pid, &exitcode, 0);;
		return(ft_free_2d(envp),exitcode);
	}
	if(execve(cmd_path, type_exec_cmd->arg_start, envp) == -1)
		{
		printf("%s: no executable found\n", type_exec_cmd->arg_start[0]);
		return(1);
		}
	return(0);
}

int exec_redir(t_cmd *cmd, char **envp, t_link_list *my_envp)
{
	t_redir_cmd	*type_redir_cmd;
	int			new_fd;
	char		*error;

	type_redir_cmd = (t_redir_cmd*)cmd;
	close(type_redir_cmd->fd);
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
	exec_cmd(type_redir_cmd->sub_cmd, envp, my_envp, false);
	close(new_fd);
	new_fd = open("/dev/tty", O_WRONLY);
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
		dup2(end[1], STDOUT_FILENO);
		exec_cmd(type_pipe_cmd->left, envp, my_envp, true);
		close(end[1]);
	}
	right = ft_fork();
	if(right == 0)
	{
		close(end[1]);
		dup2(end[0], STDIN_FILENO);
		close(end[0]);
		exec_cmd(type_pipe_cmd->right, envp, my_envp, true);
	}
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