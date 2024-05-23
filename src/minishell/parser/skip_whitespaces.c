/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   skip_whitespaces.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erybolov <erybolov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 09:15:59 by erybolov          #+#    #+#             */
/*   Updated: 2024/05/23 09:16:11 by erybolov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	skip_whitespaces(char **input)
{
	const char	whitespaces[] = " \t\r\n\v";

	while (**input && ft_strchr(whitespaces, **input))
		(*input)++;
}
