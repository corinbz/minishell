/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corin <corin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 17:39:34 by erybolov          #+#    #+#             */
/*   Updated: 2024/05/12 11:02:58 by corin            ###   ########.fr       */
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

void	minishell_run(t_minishell *m);

//Corin added from here
/*
Example for execcmd struct
..._ls_-l_-a_...
...xooxooxoox...
o --> argv
x --> eargv
*/
#define EXEC  1
#define REDIR 2
#define PIPE  3
#define LIST  4

typedef struct s_cmd
{
	int	type;
}	t_cmd;

typedef struct s_execcmd
{
	int		type;//EXEC || REDIR || PIPE || LIST
	char	*argv[10];//points to program name + flags
	char	*eargv[10];//points to the null terminator after each argv string
	//maybe we can null terminate another way?
}	t_execcmd;

typedef struct s_redircmd 
{
	int		type;
	t_cmd	*cmd;
	char	*file;//filename begin byte
	char	*efile;//filename end byte
	int		mode;//O_WRONLY|O_CREAT etc.. depends on the redir cmd > || >> || <
	int		fd;// 0 or 1 depending on what we want to redirect
}	t_redircmd;

typedef struct s_pipecmd
{
	int		type;
	t_cmd	*left;
	t_cmd	*right;
}	t_pipecmd;

#endif
