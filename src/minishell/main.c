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
	int i = 0;

	paths = get_possible_paths(envp);
	type_exec_cmd = (t_exec_cmd*)cmd;
	cmd_path = get_path(type_exec_cmd->arg_start[0], paths);
	// printf("cmd_path: %s\n", cmd_path);
	// printf("cmd args: %s\n", type_exec_cmd->arg_start[1]);
	// while(type_exec_cmd->arg_start[i])
	// {
	// 	// printf("gothere \n");
	// 	printf("cmd arg %i: %s\n", i, type_exec_cmd->arg_start[i]);
	// 	i++;
	// }
	if(execve(cmd_path, type_exec_cmd->arg_start, envp) == -1)
		{
		printf("execve failed on %s\n", type_exec_cmd->arg_start[0]);
		return(1);
		}
	return(0);
}

int exec_redir(t_cmd *cmd, char **envp)
{
	t_redir_cmd	*type_redir_cmd;
	int			new_fd;

	type_redir_cmd = (t_redir_cmd*)cmd;
	close(type_redir_cmd->fd);
	new_fd = open(type_redir_cmd->token_start_pos, (O_RDWR | O_CREAT));
	printf("new_fd is %i\n", new_fd);
	if(new_fd < 0)
	{
		// printf("failed to open %s\n", type_redir_cmd->token_start_pos);
		char *error = "failed to create file\n";
		ft_putstr_fd(error,2);
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
	int			status2;

	printf("got into pipe\n");
	type_pipe_cmd = (t_pipe_cmd*)cmd;
	if(pipe(end) < 0)
		ft_panic("pipe");
	left = ft_fork();
	if(left == 0)
	{
		printf("got inside left\n");
		close(end[0]);
		dup2(end[1], STDOUT_FILENO);
		close(end[1]);
		exec_cmd(type_pipe_cmd->left, envp);
	}

	right = ft_fork();
	if(right == 0)
	{
		printf("got inside right\n");
		close(end[1]);
		dup2(end[0], STDIN_FILENO);
		close(end[0]);
		exec_cmd(type_pipe_cmd->right, envp);
	}
	waitpid(left, &status, 0);
	// waitpid(right, &status2, 0);
	printf("inside main\n");
	return(0);
}
int exec_cmd(t_cmd *cmd, char **envp)
{

	if (cmd->type == EXEC)
		exec_exec(cmd, envp);
	if(cmd->type == REDIR)
		exec_redir(cmd, envp);
	if(cmd->type == PIPE)
		exec_pipe(cmd, envp);
	return(0);
}
// int free_cmd(t_cmd *cmd)
// {
// 	t_exec_cmd *cmde;

// 	if(cmd->type == EXEC)
// 	{
// 		cmde = (t_exec_cmd*)cmd;
// 		ft_free_2d(cmde->arg_start);
// 	}
// }
int main(int argc, char **argv, char **envp)
{
	if (argc != 1 || argv[1])
	{
		ft_panic("This program does not accept arguments\n");
		exit(0);
	}
	t_exec_cmd *mock_exec1;
	t_exec_cmd *mock_exec2;
	t_pipe_cmd *mock_pipe;
	t_redir_cmd *mock_redir;
	char *output = "output";

	mock_exec1 = (t_exec_cmd*)create_exec_cmd();
	mock_exec1->arg_start[0] = "ls";
	mock_exec1->arg_start[1] = "-l";
	mock_exec1->arg_start[2] = "-i";

	mock_exec2 = (t_exec_cmd*)create_exec_cmd();
	mock_exec2->arg_start[0] = "grep";
	mock_exec2->arg_start[1] = "README";

	mock_pipe = (t_pipe_cmd*)create_pipe_cmd((t_cmd*)mock_exec1,(t_cmd*)mock_exec2);
	mock_redir = (t_redir_cmd*)create_redir_cmd((t_cmd*)mock_pipe,output, NULL, 2 ,1 , 0);
	// exec_cmd((t_cmd*)mock_exec1, envp);
	// exec_pipe((t_cmd*)mock_pipe, envp);
	exec_redir((t_cmd*)mock_redir, envp);
	// ft_free_2d(mock_exec1->arg_start);
	free(mock_exec1);
	free(mock_exec2);
	free(mock_pipe);
	free(mock_redir);
	// free(mock_cmd);
	return (EXIT_SUCCESS);
}

/* m as variable name because later we would like to work with nested structs like m->some->struct->another
 * m is static so we don't have to set fields as NULL
 *
 * minishell_run is a program loop that will interact with user
 *
 * also we have to implement cleanup (free etc) before we exit from main
 */