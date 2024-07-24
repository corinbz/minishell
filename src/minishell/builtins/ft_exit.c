/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corin <corin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/30 16:23:38 by ccraciun          #+#    #+#             */
/*   Updated: 2024/07/24 12:16:59 by corin            ###   ########.fr       */
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

int ft_exit(t_exec_cmd *cmd, int last_status)
{
	int exit_status;
	
	exit_status = last_status % 255;
	if(cmd->arg_start[1] && cmd->arg_start[2])
	{
		printf("minishell: exit: too many arguments\n");
		return(1);
	}
	if(!cmd->arg_start[1])
	{
		// printf("exited with exitcode %d\n", exit_status);
		exit(exit_status);
	}
	exit_status = ft_atoi(cmd->arg_start[1]) % 255;
	// printf("exited with exitcode %d\n", exit_status);
	exit(exit_status);
}