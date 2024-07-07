/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccraciun <ccraciun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 14:52:26 by ccraciun          #+#    #+#             */
/*   Updated: 2024/06/02 16:39:05y ccraciun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int ft_heredoc(t_heredoc *heredoc, char **envp)
{
	char	*input;
	char	*input_newline;

	heredoc->temp_file = open("heredoc", O_CREAT | O_RDWR | O_TRUNC, DEFAULT_CHMOD);
	heredoc->eof = "eof";
	while (1)
	{
		input = readline("heredoc> ");
		if (!input)
		{
			close(heredoc->temp_file);
			exit(1); //add cleanup
		}
		if (input)
		{
			if(ft_strncmp(input,heredoc->eof,ft_strlen(heredoc->eof)) == 0)
			{
				free(input);
				close(heredoc->temp_file);
				return(0);
			}
			else
			{
				input_newline = ft_strjoin(input, "\n");
				if(!input_newline)
					return(free(input), 1);
				ft_putstr_fd(input_newline, heredoc->temp_file);
				free(input_newline);
			}
			free(input);
		}
	}
	return(0);
}
