/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccraciun <ccraciun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 11:31:10 by ccraciun          #+#    #+#             */
/*   Updated: 2024/06/30 16:35:23 by ccraciun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_pwd()
{
	char *buff;
	
	buff = getcwd(NULL, 0);
	if (buff)
	{
		printf("%s\n", buff);
		free(buff);
	}
	else
	{
		printf("getcwd error\n");
		return(1);
	}
	return(0);
}
