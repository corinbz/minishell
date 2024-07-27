/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccraciun <ccraciun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 16:46:08 by ccraciun          #+#    #+#             */
/*   Updated: 2024/07/27 13:44:43 by ccraciun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "libft.h"

void	*ft_calloc(size_t num_elements, size_t element_size)
{
	void			*result;
	unsigned char	*p;
	size_t			total_size;

	total_size = num_elements * element_size;
	result = malloc(total_size);
	if (!result)
		return (NULL);
	p = (unsigned char *)result;
	while (total_size != 0)
	{
		*p = '\0';
		p++;
		total_size--;
	}
	return (result);
}
