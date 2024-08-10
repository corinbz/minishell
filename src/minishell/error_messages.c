/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_messages.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccraciun <ccraciun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 12:23:18 by ccraciun          #+#    #+#             */
/*   Updated: 2024/08/10 12:53:31 by ccraciun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_to_stderr(const char *optional, char *message)
{
	int	stdout_fd;

	stdout_fd = dup(STDOUT_FILENO);
	dup2(STDERR_FILENO, STDOUT_FILENO);
	if (optional)
		printf("%s : %s\n", optional, message);
	else
		printf("%s\n", message);
	dup2(stdout_fd, STDOUT_FILENO);
	close(stdout_fd);
}
