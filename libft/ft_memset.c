/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okoca <okoca@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 15:03:36 by okoca             #+#    #+#             */
/*   Updated: 2024/07/31 11:30:43 by okoca            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// if (!addr)
// 	return (NULL);
// i was told to remove these protections.

inline void	*ft_memset(void *addr, int c, size_t n)
{
	size_t			i;
	unsigned char	*location;

	i = 0;
	location = (unsigned char *)addr;
	while (i < n)
	{
		location[i] = (unsigned char)c;
		i++;
	}
	return (addr);
}
