/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccraciun <ccraciun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 16:46:08 by ccraciun          #+#    #+#             */
/*   Updated: 2024/04/03 13:33:40 by ccraciun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "libft.h"

void	*ft_calloc(size_t num_elements, size_t element_size)
{
	void			*result;
	unsigned char	*p;

	result = malloc(num_elements * element_size);
	if (!result)
		return (NULL);
	p = (unsigned char *)result;
	while (num_elements != 0)
	{
		*p = '\0';
		p++;
		num_elements--;
	}
	return (result);
}
