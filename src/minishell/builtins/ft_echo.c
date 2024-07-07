/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccraciun <ccraciun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/30 16:23:38 by ccraciun          #+#    #+#             */
/*   Updated: 2024/06/30 16:27:03 by ccraciun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_echo(char *newline, char **input)
{
	int i;

	i = 1;
	if(ft_strncmp(newline, "-n", 2) == 0)
	{
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
	// i = 1;
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
