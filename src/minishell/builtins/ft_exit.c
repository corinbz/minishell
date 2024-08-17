/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corin <corin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/30 16:23:38 by ccraciun          #+#    #+#             */
/*   Updated: 2024/07/31 19:18:38 by erybolov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static bool	valid_number(char *str)
{
	int	i;

	i = 0;
	while (str && str[i])
	{
		if (!ft_isdigit(str[i]) && str[i] != '-' && str[i] != '+')
			return (false);
		i++;
	}
	return (true);
}

int	ft_exit(t_exec_cmd *cmd, int last_status)
{
	int	exit_status;

	exit_status = last_status % 256;
	if (!cmd)
	{
		exit(exit_status);
	}
	if (cmd->arg_start[1] && cmd->arg_start[2])
	{
		printf("minishell: exit: too many arguments\n");
		return (1);
	}
	if (!cmd->arg_start[1])
	{
		exit(exit_status);
	}
	if (!valid_number(cmd->arg_start[1]))
		exit(2);
	exit_status = ft_atoi(cmd->arg_start[1]) % 256;
	exit(exit_status);
}
