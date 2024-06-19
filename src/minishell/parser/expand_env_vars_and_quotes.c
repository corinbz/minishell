/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_env_vars_and_quotes.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erybolov <erybolov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 07:17:39 by erybolov          #+#    #+#             */
/*   Updated: 2024/06/19 08:58:32 by erybolov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void expand_env_vars_and_quotes(char **input, t_link_list *env)
{
	int	i;
	char	*str;

	i = 0;
	str = *input;
	while (str[i])
	{
		if (str[i] == '$')
			expand_dollar_sign(input, &str[i], env);
//		if (str[i] == '\'')
//			expand_single_quote(input, &str[i]);
//		if (str[i] == '"')
//			expand_double_quote(input, &str[i]);
		i++;
	}
}

//wrong syntax if the same symbol not found