/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corin <corin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 17:39:34 by erybolov          #+#    #+#             */
/*   Updated: 2024/07/30 21:54:29 by corin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include <readline/readline.h>
# include <readline/history.h>
# include <stdio.h>
# include <stdbool.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <stdnoreturn.h>
# include <dirent.h>
# include <linux/limits.h>
# include <signal.h>
# include <limits.h>
# include <errno.h>
# include <termios.h>

/******************************************************************************
*								CONSTANTS									  *
******************************************************************************/
# define MAX_ARGUMENTS 10
# define DEFAULT_CHMOD 0644
# define EXEC_NOT_FOUND 127

/******************************************************************************
*								GLOBAL VARIABLES							  *
******************************************************************************/
extern int	g_signal;

/******************************************************************************
*								ENUMS										  *
******************************************************************************/
typedef enum s_cmd_enum
{
	EXEC = 1,
	REDIR = 2,
	PIPE = 3,
	HEREDOC = 4
}	t_cmd_enum;

/******************************************************************************
*								STRUCTS										  *
******************************************************************************/

typedef struct s_exit_status
{
	int		exit_status;
}	t_exit_status;

typedef struct s_parser_quotes_state
{
	bool	in_single;
	bool	double_in_single;
	bool	in_double;
	bool	single_in_double;
}	t_state;

typedef struct s_cmd
{
	t_cmd_enum	type;
}	t_cmd;

typedef struct s_exec_cmd
{
	t_cmd_enum	type;
	char		*arg_start[MAX_ARGUMENTS];
	char		*arg_end[MAX_ARGUMENTS];
}	t_exec_cmd;

typedef struct s_redir_cmd
{
	t_cmd_enum	type;
	t_cmd		*sub_cmd;
	char		*token_start_pos;
	char		*token_end_pos;
	int			mode;
	int			fd;
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

/******************************************************************************
*								FUNCTIONS									  *
******************************************************************************/

/* ------------------------ CONSTRUCTOR FUNCTIONS ----------------------------*/

t_cmd		*create_exec_cmd(void);
t_cmd		*create_redir_cmd(t_cmd *sub_cmd, char *file,
				char *efile, int mode, int fd);
t_cmd		*create_pipe_cmd(t_cmd *left, t_cmd *right);
t_cmd		*create_heredoc_cmd(t_cmd *sub_cmd, char *eof_start, char *eof_end);

/* ---------------------------- UTILITY --------------------------------------*/
pid_t		ft_fork(void);
t_link_list	*create_builtin_lst(void);
char		**link_list_to_array(t_link_list **head);
int			get_set_return_val(int val);
void		free_envp(t_link_list **envp);
t_link_list	*get_last_value(t_link_list *head);
void		free_full_cmd(t_cmd *cmd);
int			get_exit_sts(t_link_list *my_envp);
int			save_original_fds(int *original_stdout_fd, int *original_stdin_fd);
int			restore_original_fds(int original_stdout_fd, int original_stdin_fd);

/* ---------------------------- PARSER ---------------------------------------*/
t_cmd		*parse_cmd(char *input);
t_cmd		*parse_pipe(char **input);
bool		is_token_ahead(char **input, char *tokens);
void		skip_whitespaces(char **input);
char		get_token(char **input, char **token_start_pos,
				char **token_end_pos);
void		ft_panic(const char *s);
t_cmd		*parse_exec(char **input);
t_cmd		*parse_redirections(t_cmd *cmd, char **input);
void		null_terminate_cmd(t_cmd *cmd);
void		expand_env_vars_and_quotes(char **input, t_link_list *env,
				t_exit_status *exit_sts);
void		expand_dollar_signs(char *i, t_link_list *env);
bool		try_to_expand_dollar_sign(char *s, t_link_list *env, t_state state);
void		expand_quotes(char *str);
// char		*replace_ret_value(const char *input, int ret_value, int pos);
void		add_exit_status_to_envp(t_link_list **my_envp,
				t_exit_status *exit_sts);
bool		is_heredoc_cmd(t_cmd *cmd);

/* ---------------------------- BUILTIN --------------------------------------*/
t_link_list	*create_my_envp(char **envp);
int			ft_pwd(void);
int			ft_env(t_link_list *head);
int			ft_export(char *new_param, t_link_list *head);
int			ft_unset(char *param, t_link_list **head);
int			ft_echo(char *newline, char **input);
int			ft_cd(char *dir, t_link_list *my_envp);
int			ft_exit(t_exec_cmd *cmd, int last_status);
int			builtin_type(t_exec_cmd *cmd);
int			run_builtin_parent(t_exec_cmd *cmd, t_link_list *my_envp);
int			run_builtin_child(t_exec_cmd *cmd, t_link_list *my_envp);

/* ---------------------------- EXECUTOR -------------------------------------*/
int			exec_pipe(t_cmd *cmd, char **envp, t_link_list *my_envp);
int			exec_redir(t_cmd *cmd, char **envp, t_link_list *my_envp);
char		**get_possible_paths(char **envp);
char		*get_path(char *cmd, char **paths);
int			exec_cmd(t_cmd *cmd, char **envp,
				t_link_list *my_envp, bool is_child);
void		minishell_run(char **envp, t_link_list *my_envp,
				t_exit_status *exit_sts);
int			exec_heredoc(t_cmd *cmd, char **envp, t_link_list *my_envp);

/* ---------------------------- heredoc --------------------------------------*/
char		*create_new_eof(const char *eof_start, const char *eof_end);
int			copy_file_to_fd(const char *src_path, int dest_fd);
int			duplicate_stdin(int *original_stdin);
int			close_temp_fd_and_unlink(int temp_fd, const char *file);
int			open_heredoc_file(int *temp_fd);
/* ------------------------------ SIGNALS ------------------------------------*/
void		run_signals(int sig);
void		restore_prompt(int sig);
void		ctrl_c(int sig);
void		back_slash(int sig);

/* ------------------------ DEBUGGING HELPER ---------------------------------*/
void		print_cmd_structure(t_cmd *cmd, int indent);

#endif
