/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okoca <okoca@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 08:44:50 by okoca             #+#    #+#             */
/*   Updated: 2024/08/02 17:00:41 by okoca            ###   ########.fr       */
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

t_map	init_map(t_ctx *ctx)
{
	t_map	map;

	map.player.pos.x = ctx->mapdata->player_pos.x - 0.5f;
	map.player.pos.y = ctx->mapdata->player_pos.y - 0.5f;
	map.player.dir.x = -1.0f;
	map.player.dir.y = 0.0f;
	map.player.plane.x = 0;
	map.player.plane.y = 0.60;
	map.map = ctx->mapdata->map;
	map.width = 0;
	map.height = 0;
	while (map.map[map.height])
		map.height++;
	if (map.height)
		map.width = ft_strlen(map.map[0]);
	return (map);
}
