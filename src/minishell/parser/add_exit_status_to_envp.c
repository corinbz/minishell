/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_exit_status_to_envp.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corin <corin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 18:08:52 by erybolov          #+#    #+#             */
/*   Updated: 2024/07/25 10:34:03 by corin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void add_exit_status_to_envp(t_link_list **my_envp, t_exit_status *exit_sts)
{
	t_link_list	*node;
	char	*value;
	char	*exit_status;

	exit_status = ft_itoa(exit_sts->exit_status % 255);
	value = ft_strjoin("?=", exit_status);
	if(!value)
		ft_panic("minishell: malloc failed (add_exit_status_to_envp)\n");
	ft_export(value, *my_envp);
	free(value);
	free(exit_status);
	// node = ft_lstnew(value);
	// ft_lstadd_front(my_envp, node);
}