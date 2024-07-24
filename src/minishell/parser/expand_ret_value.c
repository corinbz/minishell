/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_ret_value.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corin <corin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 11:49:11 by corin             #+#    #+#             */
/*   Updated: 2024/07/24 12:24:40 by corin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"


// Helper function to replace the "$?" sequence with the return value
char *replace_ret_value(const char *input, int ret_value, int pos)
{
	char *ret_val_str;
	char *new_str;
	char *temp;

	ret_value = ret_value % 255;
	ret_val_str = ft_itoa(ret_value);
	if (!ret_val_str)
		ft_panic("minishell: ft_itoa failed\n");
	temp = ft_substr(input, 0, pos);
	if (!temp)
		ft_panic("minishell: ft_substr failed\n");
	new_str = ft_strjoin(temp, ret_val_str);
	if (!new_str)
		ft_panic("minishell: ft_strjoin failed\n");
	free(temp);
	free(ret_val_str);
	temp = ft_strjoin(new_str, input + pos + 2);
	if (!temp)
		ft_panic("minishell: ft_strjoin failed\n");
	free(new_str);
	return (temp);
}

// Main function to expand return value in the input string
char *expand_ret_value(const char *input, t_exit_status *exit_sts)
{
	char *new_input;
	int i;
	
	if (!input)
		return (NULL);
	new_input = ft_strdup(input);
	if (!new_input)
		ft_panic("minishell: ft_strdup failed\n");
	i = 0;
	while (new_input[i])
	{
		if (new_input[i] == '$' && new_input[i + 1] == '?')
		{
			char *temp = replace_ret_value(new_input, exit_sts->exit_status, i);
			free(new_input);
			new_input = temp;
			i += ft_strlen(temp) - ft_strlen(new_input); // Move index to after the replaced value
		}
		else
			i++;
	}
	return (new_input);
}
