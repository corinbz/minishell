/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccraciun <ccraciun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 17:39:34 by erybolov          #+#    #+#             */
/*   Updated: 2024/07/01 15:34:16 by ccraciun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

#include "../../libft/libft.h"
#include <readline/readline.h>
#include <readline/history.h>
#include <stdio.h>
#include <stdbool.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <dirent.h>
#include <linux/limits.h>
#include <signal.h>

int sig_ret_value;
typedef struct s_minishell
{
	t_list	*input_history;
}	t_minishell;

#define MAX_ARGUMENTS 10
#define DEFAULT_CHMOD 0644

typedef enum s_cmd_enum
{
	EXEC =  1,
	REDIR = 2,
	PIPE  = 3,
	HEREDOC = 4
}	t_cmd_enum;

typedef struct s_link_list
{
	char *param;
	struct s_link_list *next;
}	t_link_list;

typedef struct s_cmd
{
	t_cmd_enum	type;
}	t_cmd;

typedef struct s_exec_cmd
{
	t_cmd_enum	type;//EXEC || REDIR || PIPE
	char		*arg_start[MAX_ARGUMENTS];//points to program name + flags (token_start)
	char 		*arg_end[MAX_ARGUMENTS];//points to the null terminator after each arg_start string (token_end)
	//arg_start and arg_end NULL terminated
}	t_exec_cmd;

typedef struct s_heredoc
{
	bool	is_true;
	int		temp_file;
	char	*eof;
}	t_heredoc;

typedef struct s_redir_cmd
{
	t_cmd_enum	type;
	t_cmd		*sub_cmd;
	char		*token_start_pos;//filename or delimiter for << begin byte
	char		*token_end_pos;//filename or delimiter for << end byte
	int			mode;//O_WRONLY|O_CREAT etc.. depends on the redir cmd > || >> || <
	int			fd;// 0 or 1 depending on what we want to redirect
}	t_redir_cmd;

typedef struct s_pipe_cmd
{
	t_cmd_enum	type;
	t_cmd		*left;
	t_cmd		*right;
}	t_pipe_cmd;

typedef struct s_heredoc_cmd
{
	t_cmd_enum	type;
	t_cmd		*sub_cmd;
	char		*eof_start;
	char		*eof_end;
	int			temp_fd;
}	t_heredoc_cmd;

//constructor functions
t_cmd	*create_exec_cmd(void);
t_cmd	*create_redir_cmd(t_cmd *sub_cmd, char *file, char *efile, int mode, int fd);
t_cmd	*create_pipe_cmd(t_cmd *left, t_cmd *right);
t_cmd	*create_heredoc_cmd(t_cmd *sub_cmd, char *eof_start, char *eof_end);

//utils
pid_t		ft_fork(void);
t_link_list	*create_builtin_lst();
char		**link_list_to_array(t_link_list **head);

//parser functions
t_cmd	*parse_cmd(char *input);
t_cmd	*parse_pipe(char **input);
bool	is_token_ahead(char **input, char *tokens);
void	skip_whitespaces(char **input);
char	get_token(char **input, char **token_start_pos, char **token_end_pos);
void	ft_panic(const char *s);
t_cmd	*parse_exec(char **input);
t_cmd	*parse_redirections(t_cmd *cmd, char **input);
void	null_terminate_cmd(t_cmd *cmd);
void	expand_env_vars_and_quotes(char **input, t_link_list *env);
char	*expand_dollar_sign(char *dollar_pos, t_link_list *env);
char	*expand_single_quote(char *quote_start, t_link_list *env);
char	*expand_multiple_single_quotes(char *quote_start, t_link_list *env, int quotes_amount);

//builtins
t_link_list	*create_my_envp(char **envp);
int			ft_pwd();
int			ft_env(t_link_list *head);
int			ft_export(char *new_param, t_link_list *head);
int			ft_unset(char *param, t_link_list **head);
int			ft_echo(char *newline, char **input);
int			ft_cd(char *dir, t_link_list *my_envp);

int			builtin_type(t_exec_cmd *cmd);
int			run_builtin_parent(t_exec_cmd *cmd, t_link_list *my_envp);
int			run_builtin_child(t_exec_cmd *cmd, t_link_list *my_envp);

//envp
void		free_envp(t_link_list **envp);
t_link_list	*get_last_value(t_link_list *head);

//executor
char	**get_possible_paths(char **envp);
char	*get_path(char *cmd, char **paths);
int		exec_cmd(t_cmd *cmd, char **envp, t_link_list *my_envp, bool is_child);
void	minishell_run(t_minishell *m,char **envp, t_link_list *my_envp);
//heredoc
int ft_heredoc(t_heredoc *heredoc, char **envp);

#endif
