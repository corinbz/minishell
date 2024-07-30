/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corin <corin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/30 16:23:38 by ccraciun          #+#    #+#             */
/*   Updated: 2024/07/31 19:13:01 by erybolov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static bool	digits_exclusive(char *str)
{
	int	i;

	i = 0;
	while (str && str[i])
	{
		if (!ft_isdigit(str[i]))
			return (false);
		i++;
	}
	return (true);
}

int	ft_exit(t_exec_cmd *cmd, int last_status)
{
	int	exit_status;

	exit_status = last_status % 256;
	if (cmd->arg_start[1] && cmd->arg_start[2])
	{
		printf("minishell: exit: too many arguments\n");
		return (1);
	}
	if (!cmd->arg_start[1])
	{
		exit(exit_status);
	}
	if (!digits_exclusive(cmd->arg_start[1]))
		exit(2);
	exit_status = ft_atoi(cmd->arg_start[1]) % 256;
	exit(exit_status);
}
