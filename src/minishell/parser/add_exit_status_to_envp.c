/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_exit_status_to_envp.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erybolov <erybolov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 18:08:52 by erybolov          #+#    #+#             */
/*   Updated: 2024/07/24 18:49:13 by erybolov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void add_exit_status_to_envp(t_link_list **my_envp, t_exit_status *exit_sts)
{
	t_link_list	*node;
	char	*value;

	value = ft_strjoin("?=", ft_itoa(exit_sts->exit_status % 255));
	node = ft_lstnew(value);
	ft_lstadd_front(my_envp, node);
}