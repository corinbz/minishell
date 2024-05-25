/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   skip_whitespaces.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccraciun <ccraciun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 09:15:59 by erybolov          #+#    #+#             */
/*   Updated: 2024/05/25 15:48:28 by ccraciun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	skip_whitespaces(char **input)
{
	const char	whitespaces[] = " \t\r\n\v";

	while (**input && ft_strchr(whitespaces, **input))
		(*input)++;
}
