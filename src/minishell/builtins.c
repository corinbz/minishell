/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccraciun <ccraciun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 11:31:10 by ccraciun          #+#    #+#             */
/*   Updated: 2024/05/25 11:45:42 by ccraciun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
/*
echo with option -n
◦ cd with only a relative or absolute path
◦ pwd with no options
◦ export with no options
◦ unset with no options
◦ env with no options or arguments
◦ exit with no options
*/

void ft_pwd(char **envp)
{
	int	i;

	i = 0;
	while(envp[i])
	{
		if(ft_strncmp("PWD", envp[i], 3) == 0)
		{
			printf("%s\n", envp[i] + 4);
			return ;
		}
		i++;
	}
	printf("PWD not found\n");
}