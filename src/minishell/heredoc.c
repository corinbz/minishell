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

int ft_heredoc(char *eof, char **envp)
{
	char *input;
	char *ret;
	char *new_ret;
	char *input_newline;

	ret = ft_calloc(1,1);
	// input_newline = ft_calloc(1,1);
	while (1)
	{
		input = readline("heredoc> ");
		if (!input)
		{
			printf("exit\n");
			exit(0); //add cleanup
		}
		if (input)
		{
			if(ft_strncmp(input,eof,ft_strlen(eof)) == 0)
			{
				printf("heredoc result -> %s",ret);
				free(ret);
				free(input);
				return(0);
			}
			else
			{
				input_newline = ft_strjoin("\n", input);
				new_ret = ft_strjoin(ret, input_newline);
				free(ret);
				free(input_newline);
				ret = new_ret;
			}
			free(input);
		}
	}
	return(1);
}