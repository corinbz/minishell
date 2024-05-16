/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corin <corin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 10:31:39 by corin             #+#    #+#             */
/*   Updated: 2024/05/16 18:45:12 by erybolov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_panic(const char *s)
{
	ft_putstr_fd(s, STDERR_FILENO);
	exit(EXIT_FAILURE);
}

//fork with error handling
int	ft_fork(void)
{
	int	pid;

	pid = fork();
	if (pid == -1)
		ft_panic("Fork failed\n");
	return (pid);
}