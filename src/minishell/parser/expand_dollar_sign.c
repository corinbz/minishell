/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_dollar_sign.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erybolov <erybolov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 08:26:14 by erybolov          #+#    #+#             */
/*   Updated: 2024/06/19 09:26:09 by erybolov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void replace_var_with_val(char **input, const char *dollar_start, const char *dollar_end, char *val)
{
	char *i;
	char *result;
	char *result_i;

	i = *input;
	result = malloc(ft_strlen(*input) + ft_strlen(val));
	if (!result)
		ft_panic("minishell: malloc failed\n");
	result_i = result;
	while (i < dollar_start)
	{
		*result_i = *i;
		result_i++;
		i++;
	}
	while (*val)
	{
		*result_i = *val;
		result_i++;
		val++;
	}
	while (*dollar_end)
	{
		*result_i = *dollar_end;
		result_i++;
		dollar_end++;
	}
	*result_i = '\0';
	free(*input);
	*input = result;
}

static char *try_to_get_val_from_env(char *var, t_link_list *env)
{
	char **splitted_env;

	while (env)
	{
		if (ft_strncmp(env->param, var, ft_strlen(var)) == 0)
			break ;
		env = env->next;
	}
	if (env)
	{
		splitted_env = ft_split(env->param, '=');
		if (!splitted_env)
			ft_panic("minishell: ft_split failed\n");
		free(splitted_env[0]);
		return (splitted_env[1]);
	}
	else
		return (ft_strdup(""));
}

void expand_dollar_sign(char **input, char *dollar_pos, t_link_list *env)
{
	char *var;
	char *val;
	char *dollar_end;
	int i;
	const char	whitespaces[] = " \t\r\n\v";

	var = malloc(ft_strlen(*input));
	if (!var)
		ft_panic("minishell: malloc failed\n");
	i = 0;
	while (dollar_pos[i + 1] && !ft_strchr(whitespaces, dollar_pos[i + 1]))
	{
		var[i] = dollar_pos[i + 1];
		i++;
	}
	var[i] = '\0';
	dollar_end = &dollar_pos[i + 1];
	val = try_to_get_val_from_env(var, env);
	free(var);
	replace_var_with_val(input, dollar_pos, dollar_end, val);
	free(val);
}

//todo works with USER, test with COLORTERM etc, simplify