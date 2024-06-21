/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_dollar_sign.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erybolov <erybolov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 08:26:14 by erybolov          #+#    #+#             */
/*   Updated: 2024/06/21 18:41:44 by erybolov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char *replace_var_with_val(char **input, const char *dollar_start, const char *dollar_end, char *val)
{
	char *i;
	char *result;
	char *result_i;
	char *to_ret;

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
	to_ret = result_i;
	while (*dollar_end)
	{
		*result_i = *dollar_end;
		result_i++;
		dollar_end++;
	}
	*result_i = '\0';
	free(*input);
	*input = result;
	return (to_ret);
}

static char *try_to_get_val_from_env(char *var, t_link_list *env)
{
	char *to_ret;

	while (env)
	{
		if (ft_strncmp(env->param, var, ft_strlen(var)) == 0 && env->param[ft_strlen(var)] == '=')
		{
			to_ret = ft_strdup(env->param + ft_strlen(var) + 1);
			if (!to_ret)
				ft_panic("minishell: ft_strdup failed\n");
			return (to_ret);
		}
		env = env->next;
	}
	return (ft_strdup(""));
}

char *expand_dollar_sign(char **input, char *dollar_pos, t_link_list *env)
{
	char *var;
	char *val;
	char *dollar_end;
	char *to_ret;
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
	to_ret = replace_var_with_val(input, dollar_pos, dollar_end, val);
	free(val);
	return (to_ret);
}
