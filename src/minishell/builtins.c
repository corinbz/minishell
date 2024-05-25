/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccraciun <ccraciun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 11:31:10 by ccraciun          #+#    #+#             */
/*   Updated: 2024/05/25 12:20:30 by ccraciun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
/*
done:
pwd with no options
env with no options or arguments

todo:
echo with option -n
cd with only a relative or absolute path
export with no options
unset with no options
exit with no options
*/

void	ft_pwd(char **envp)
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

void	ft_env(char **envp)
{
	int	i;

	i = 0;
	while(envp && envp[i])
	{
		printf("%s\n", envp[i]);
		i++;
	}
}

// void	ft_export(char *var_name, char *var_value, char **envp)
// {
	
// }