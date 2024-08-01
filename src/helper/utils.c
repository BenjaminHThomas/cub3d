/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okoca <okoca@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 20:05:52 by okoca             #+#    #+#             */
/*   Updated: 2024/08/01 20:06:00 by okoca            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

inline int	cb_max(int a, int b)
{
	if (a > b)
		return (a);
	return (b);
}

inline int	cb_min(int a, int b)
{
	if (a < b)
		return (a);
	return (b);
}