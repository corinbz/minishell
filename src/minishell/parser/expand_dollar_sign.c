/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_dollar_sign.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corin <corin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 08:26:14 by erybolov          #+#    #+#             */
/*   Updated: 2024/07/30 11:23:03 by erybolov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	expand_dollar_signs(char *str, t_link_list *env)
{
	t_state	state;

	while (true)
	{
		state.in_single = false;
		state.double_in_single = false;
		state.in_double = false;
		state.single_in_double = false;
		if (try_to_expand_dollar_sign(str, env, state) == false)
			break ;
	}
}
