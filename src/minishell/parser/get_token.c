/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_token.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erybolov <erybolov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 08:17:49 by erybolov          #+#    #+#             */
/*   Updated: 2024/05/23 09:22:49 by erybolov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	token_switch(char **input_ptr, char **token_start_pos, char **token_end_pos)
{
	char	token;

	token = **token_start_pos;
	if (**input_ptr == '|')
		(*input_ptr)++;
	else if (**input_ptr == '>')
	{
		(*input_ptr)++;
		if (**input_ptr == '>')
		{
			token = '+';
			(*input_ptr)++;
		}
	}
	else if (**input_ptr == '<')
	{
		(*input_ptr)++;
		if (**input_ptr == '<')
		{
			token = '-';
			(*input_ptr)++;
		}
	}
	else
	{
		token = 'a';
		while (**input_ptr && !ft_strchr(" \t\r\n\v|<>", **input_ptr))
			(*input_ptr)++;
	}
	*token_end_pos = *input_ptr;
	skip_whitespaces(input_ptr);
	return (token);
}

char	get_token(char **input, char **token_start_pos, char **token_end_pos)
{
	char		token;

	skip_whitespaces(input);
	*token_start_pos = *input;
	if (**input)
		token = token_switch(input, token_start_pos, token_end_pos);
	else
		token = '\0';
	*token_end_pos = *input;
	skip_whitespaces(input);
	return (token);
}
