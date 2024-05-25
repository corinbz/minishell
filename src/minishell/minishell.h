/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccraciun <ccraciun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 17:39:34 by erybolov          #+#    #+#             */
/*   Updated: 2024/05/25 13:30:41 by ccraciun         ###   ########.fr       */
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


typedef struct s_minishell
{
	t_list	*input_history;
}	t_minishell;

//Corin added from here
/*
Example for execcmd struct
..._ls_-l_-a_...
...xooxooxoox...
o --> argv
x --> eargv
*/

#define MAX_ARGUMENTS 10

typedef enum s_cmd_enum
{
	EXEC =  1,
	REDIR = 2,
	PIPE  = 3
}	t_cmd_enum;

typedef struct s_cmd
{
	t_cmd_enum	type;
}	t_cmd;

typedef struct s_exec_cmd
{
	t_cmd_enum	type;//EXEC || REDIR || PIPE
	char		*argv[MAX_ARGUMENTS];//points to program name + flags (token_start)
	char 		*eargv[MAX_ARGUMENTS];//points to the null terminator after each argv string (token_end)
	//argv and eargv NULL terminated
}	t_exec_cmd;

typedef struct s_redir_cmd
{
	t_cmd_enum	type;
	t_cmd		*cmd;
	char		*token_start_pos;//filename or delimiter for << begin byte
	char		*token_end_pos;//filename or delimiter for << end byte
	int			mode;//O_WRONLY|O_CREAT etc.. depends on the redir cmd > || >> || <
	int			fd;// 0 or 1 depending on what we want to redirect
	bool		heredoc; //true if << ; otherwise false
}	t_redir_cmd;

typedef struct s_pipe_cmd
{
	t_cmd_enum	type;
	t_cmd		*left;
	t_cmd		*right;
}	t_pipe_cmd;

//constructor functions
t_cmd	*create_exec_cmd(void);
t_cmd	*create_redir_cmd(t_cmd *subcmd, char *file, char *efile, int mode, int fd, bool heredoc);
t_cmd	*create_pipe_cmd(t_cmd *left, t_cmd *right);

//parser functions
t_cmd	*parse_cmd(char *input);
t_cmd	*parse_pipe(char **input);
bool	is_token_ahead(char **input, char *tokens);
void	skip_whitespaces(char **input);
char	get_token(char **input, char **token_start_pos, char **token_end_pos);
void	ft_panic(const char *s);
t_cmd	*parse_exec(char **input);
t_cmd	*parse_redirections(t_cmd *cmd, char **input);

//builtins
void	ft_pwd();
void	ft_env(char **envp);

#endif
