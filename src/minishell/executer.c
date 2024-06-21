/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccraciun <ccraciun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 16:51:21 by ccraciun          #+#    #+#             */
/*   Updated: 2024/06/21 12:31:35 by ccraciun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	run_cmd(t_exec_cmd *cmd, t_link_list *my_envp)
{
	if(ft_strncmp(cmd->arg_start[0], "cd", 2) == 0)
		return(2);// ft_cd();//todo
	if(ft_strncmp(cmd->arg_start[0], "exit", 4) == 0)
		return(2);// ft_exit();//todo
	if(ft_strncmp(cmd->arg_start[0], "env", 3) == 0)
		return(ft_env(my_envp), 0);
	if(ft_strncmp(cmd->arg_start[0], "pwd", 3) == 0)
		return(ft_pwd(), 0);
	if(ft_strncmp(cmd->arg_start[0], "echo", 4) == 0)
		return(ft_echo(cmd->arg_start[1], cmd->arg_start[2]), 0);
	if(ft_strncmp(cmd->arg_start[0], "export", 6) == 0)
		return(ft_export(cmd->arg_start[1], my_envp), 0);
	if(ft_strncmp(cmd->arg_start[0], "unset", 5) == 0)
		return(ft_unset(cmd->arg_start[1], &my_envp));
	return(1);
}
int	exec_exec(t_cmd *cmd, char **envp, t_link_list *my_envp)
{
	char		**paths;
	char		*cmd_path;
	t_exec_cmd	*type_exec_cmd;
	t_link_list	*builtins;
	
	type_exec_cmd = (t_exec_cmd*)cmd;
	// builtins = create_builtin_lst();
	// ft_free_2d(new_envp);
	if(run_cmd(type_exec_cmd, my_envp) == 0)
	{
		// free_envp(&my_envp);
		// ft_env(my_envp);
		free(cmd);
		exit(0);
	}
	char **new_envp = link_list_to_array(&my_envp);
	// for(int i = 0; new_envp[i]; i++)
	// {
	// 	printf("%s\n", new_envp[i]);
	// }
	paths = get_possible_paths(new_envp);
	cmd_path = get_path(type_exec_cmd->arg_start[0], paths);
	if(execve(cmd_path, type_exec_cmd->arg_start, new_envp) == -1)
		{
		printf("execve failed on %s\n", type_exec_cmd->arg_start[0]);
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
	exec_cmd(type_redir_cmd->sub_cmd, envp, my_envp);
	close(new_fd);
	return (0);
}

int exec_pipe(t_cmd *cmd, char **envp, t_link_list *my_envp)
{
	int			end[2];
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
		close(end[1]);
		exec_cmd(type_pipe_cmd->left, envp, my_envp);
	}
	right = ft_fork();
	if(right == 0)
	{
		close(end[1]);
		dup2(end[0], STDIN_FILENO);
		close(end[0]);
		exec_cmd(type_pipe_cmd->right, envp, my_envp);
	}
	close(end[0]);
	close(end[1]);
	waitpid(left, NULL, 0);
	waitpid(right, NULL, 0);
	return(0);
}
int exec_cmd(t_cmd *cmd, char **envp, t_link_list *my_envp)
{

	if (cmd->type == EXEC)
		exec_exec(cmd, envp, my_envp);
	if(cmd->type == REDIR)
		exec_redir(cmd, envp, my_envp);
	if(cmd->type == PIPE)
		exec_pipe(cmd, envp, my_envp);
	return(0);
}