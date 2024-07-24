/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corin <corin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/30 16:23:38 by ccraciun          #+#    #+#             */
/*   Updated: 2024/07/20 11:55:41 by corin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int echo_no_newline(char *newline, char **input)
{
	int	i;

	i = 1;
	while(newline[i] == 'n')
			{
				i++;
				if (newline[i] != 'n' && newline[i] != '\0')
				{
					i = 1;
					printf("%s ",newline);
					while(input[++i])
						printf("%s\n",input[i]);
					return (0);
				}
			}
		i = 2;
		while(input[i])
		{
			printf("%s", input[i]);
			i++;
			if(input[i])
				printf(" ");
		}
		return (0);
}

int	ft_echo(char *newline, char **input)
{
	int i;

	i = 1;
	if(!input || !newline)
		return(printf("\n"),0);
	if(ft_strncmp(newline, "-n", 2) == 0)
	{
		return(echo_no_newline(newline, input));
	}
	while(input[i])
	{
		printf("%s", input[i]);
		i++;
		if(input[i])
			printf(" ");
	}
	printf("\n");
	return(0);
}
