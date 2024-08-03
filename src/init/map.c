/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okoca <okoca@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 08:44:50 by okoca             #+#    #+#             */
/*   Updated: 2024/08/03 09:30:54 by okoca            ###   ########.fr       */
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

void	init_direction(t_ctx *ctx, t_map *map)
{
	int			angle;
	float		radiant;
	t_direction	dir;

	angle = 0;
	dir = ctx->mapdata->player_dir;
	if (dir == WEST)
		angle = 0;
	else if (dir == SOUTH)
		angle = 90;
	else if (dir == EAST)
		angle = 180;
	else if (dir == NORTH)
		angle = 270;
	radiant = angle * M_PI / 180.0f;
	map->player.dir.x = cos(radiant);
	map->player.dir.y = sin(radiant);
	map->player.plane.x = -0.66f * sin(radiant);
	map->player.plane.y = 0.66f * cos(radiant);
}

t_map	init_map(t_ctx *ctx)
{
	t_map	map;

	init_direction(ctx, &map);
	map.player.pos.x = ctx->mapdata->player_pos.x + 0.5f;
	map.player.pos.y = ctx->mapdata->player_pos.y + 0.5f;
	map.ceilling = ctx->mapdata->c_colour;
	map.floor = ctx->mapdata->f_colour;
	map.map = ctx->mapdata->map;
	map.width = 0;
	map.height = 0;
	while (map.map[map.height])
		map.height++;
	if (map.height)
		map.width = ft_strlen(map.map[0]);
	return (map);
}
