/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_input_valid.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erybolov <erybolov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 14:20:39 by erybolov          #+#    #+#             */
/*   Updated: 2024/08/17 14:30:05 by erybolov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

bool	is_input_valid(char *input)
{
    int i;
    int single_q;
    int double_q;

    i = 0;
    single_q = 0;
    double_q = 0;
    if (!input || !*input)
        return (false);
    if (input[0] == '|')
        return (false);
    while (input[i] != '\0')
    {
        if (input[i] == '\'')
            single_q++;
        if (input[i] == '\"')
            double_q++;
        i++;
    }
    if (single_q % 2 != 0 || double_q % 2 != 0)
        return (false);
    return (true);
}