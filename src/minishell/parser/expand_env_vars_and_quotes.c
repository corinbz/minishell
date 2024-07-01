/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_env_vars_and_quotes.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erybolov <erybolov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 07:17:39 by erybolov          #+#    #+#             */
/*   Updated: 2024/07/01 06:56:55 by erybolov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void expand_env_vars_and_quotes(char **input, t_link_list *env)
{
	char	*i;

	i = malloc(ft_strlen(*input) * 10); //dirty hack to avoid tedious calculations for now
	if (!i)
		ft_panic("minishell: malloc failed\n");
	ft_memcpy(i, *input, ft_strlen(*input) + 1); //todo check if works correctly
	free(*input);
	*input = i;
	while (*i)
	{
		if (*i == '$')
			i = expand_dollar_sign(i, env);
		else if (*i == '\'')
			i = expand_single_quote(i, env); //todo wip
		else if (*i)
			i++;
//		if (*i == '"')
//			expand_double_quote(input, i);
	}

}

