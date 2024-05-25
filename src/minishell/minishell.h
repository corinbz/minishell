/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccraciun <ccraciun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 17:39:34 by erybolov          #+#    #+#             */
/*   Updated: 2024/05/25 13:20:18 by ccraciun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

#include "../../libft/libft.h"
#include <readline/readline.h>
#include <readline/history.h>
#include <stdio.h>


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
typedef enum s_cmd_type
{
	EXEC =  1,
	REDIR = 2,
	PIPE  = 3,
} t_cmd_type;

typedef struct s_cmd
{
	int	type;
}	t_cmd;

typedef struct s_exec_cmd
{
	int		type;//EXEC || REDIR || PIPE 
	char	*argv[10];//points to program name + flags
	char	*eargv[10];//points to the null terminator after each argv string
	//maybe we can null terminate another way?
}	t_exec_cmd;

typedef struct s_redir_cmd 
{
	int		type;
	t_cmd	*cmd;
	char	*file;//filename begin byte
	char	*efile;//filename end byte
	int		mode;//O_WRONLY|O_CREAT etc.. depends on the redir cmd > || >> || <
	int		fd;// 0 or 1 depending on what we want to redirect
}	t_redir_cmd;

typedef struct s_pipe_cmd
{
	int		type;
	t_cmd	*left;
	t_cmd	*right;
}	t_pipe_cmd;

// void	minishell_run(t_minishell *m);
//constructor functions
t_cmd*	execcmd(void);
t_cmd*	redircmd(t_cmd *subcmd, char *file, char *efile, int mode, int fd);

//builtins
void	ft_pwd();
void	ft_env(char **envp);
#endif
