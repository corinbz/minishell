/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_env_vars_and_quotes.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erybolov <erybolov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 07:17:39 by erybolov          #+#    #+#             */
/*   Updated: 2024/06/22 21:09:41 by erybolov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void expand_env_vars_and_quotes(char **input, t_link_list *env)
{
	char	*i;

	i = *input;
	while (*i)
	{
		if (*i == '$')
			i = expand_dollar_sign(input, i, env);
		if (*i == '\'')
			i = expand_single_quote(i); //todo wip
//		if (str[i] == '"')
//			expand_double_quote(input, &str[i]);
		i++;
	}

}

