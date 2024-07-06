/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccraciun <ccraciun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/30 16:23:38 by ccraciun          #+#    #+#             */
/*   Updated: 2024/07/06 15:21:15 by ccraciun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	get_set_return_val(int val)
{
	static int ret;

	if(val == INT_MIN)
	{
		printf("ret is %d\n", ret);
		return(ret);
	}
	ret = val;
	return(ret);
	
}

int ft_exit(char *my_status, int last_status)
{
	int exit_status;
	
	exit_status = last_status % 255;
	printf("exited\n");
	if(!my_status)
	{
		// printf("exited with exitcode %d\n", exit_status);
		exit(exit_status);
	}
	exit_status = ft_atoi(my_status) % 255;
	// printf("exited with exitcode %d\n", exit_status);
	exit(exit_status);
}