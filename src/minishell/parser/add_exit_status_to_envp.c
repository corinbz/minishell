/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_exit_status_to_envp.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corin <corin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 18:08:52 by erybolov          #+#    #+#             */
/*   Updated: 2024/07/25 10:04:25 by corin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void add_exit_status_to_envp(t_link_list **my_envp, t_exit_status *exit_sts)
{
	t_link_list	*node;
	char	*value;

	value = ft_strjoin("?=", ft_itoa(exit_sts->exit_status % 255));
	ft_export(value, *my_envp);
	// node = ft_lstnew(value);
	// ft_lstadd_front(my_envp, node);
}