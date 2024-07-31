/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okoca <okoca@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 08:44:50 by okoca             #+#    #+#             */
/*   Updated: 2024/07/31 16:19:19 by okoca            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	print_map(char *map, int height, int width)
{
	int	i;

	i = 0;
	while (i < height)
	{
		printf("%.12s\n", &(map[i * width]));
		i++;
	}
}

/*
* 111111111111
* 100000000001
* 100000000001
* 10P000111001
* 100000110001
* 100000001001
* 100000000001
* 100000000001
* 100000000001
* 111111111111
*/
t_map	init_map(void)
{
	t_map	map;

	map.player.x = 3.0f;
	map.player.y = 3.0f;
	map.player.dx = -1.0f;
	map.player.dy = 0.0f;
	map.player.angle = 0.0f;
	map.player.plane_x = 0;
	map.player.plane_y = 0.60;
	map.height = 10;
	map.width = 12;
	map.raw = ft_calloc(sizeof(char), (map.height * map.width + 1));
	if (!map.raw)
		return (map);
	ft_strcat(map.raw, "111111111111100000000001100000000001100000111001100000110001100000001001100000000001100000000001101000000001111111111111");
	print_map(map.raw, map.height, map.width);
	return (map);
}
