/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_token.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erybolov <erybolov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 08:17:49 by erybolov          #+#    #+#             */
/*   Updated: 2024/06/08 18:02:29 by erybolov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	token_switch(char **input)
{
	char	token;

	token = **input;
	if (**input == '|')
		(*input)++;
	else if (**input == '>')
	{
		(*input)++;
		if (**input == '>')
		{
			token = '+';
			(*input)++;
		}
	}
	else if (**input == '<')
	{
		(*input)++;
		if (**input == '<')
		{
			token = '-';
			(*input)++;
		}
	}
	else
	{
		token = 'a';
		while (**input && !ft_strchr("\t\r\n\v>< |", **input))
			(*input)++;
	}
	return (token);
}

char	get_token(char **input, char **token_start_pos, char **token_end_pos)
{
	char		token;

	skip_whitespaces(input);
	if (token_start_pos)
		*token_start_pos = *input;
	if (**input)
		token = token_switch(input);
	else
		token = '\0';
	if (token_end_pos)
		*token_end_pos = *input;
	skip_whitespaces(input);
	return (token);
}
