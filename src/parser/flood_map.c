/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bthomas <bthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 14:38:59 by bthomas           #+#    #+#             */
/*   Updated: 2024/08/02 14:58:29 by bthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static void	flood_fill(char **map, int y, int x, int height, int width)
{
	if (y <= 0 || y >= height || x <= 0 || x >= width
		|| in(map[y][x], "NSEW1Z"))
		return ;
	map[y][x] = 'Z';
	flood_fill(map, y - 1, x, height, width);
	flood_fill(map, y + 1, x, height, width);
	flood_fill(map, y, x - 1, height, width);
	flood_fill(map, y, x + 1, height, width);
}

static void	call_flood(char	**map, int y, int x, int height, int width)
{
	flood_fill(map, y - 1, x, height, width);
	flood_fill(map, y + 1, x, height, width);
	flood_fill(map, y, x - 1, height, width);
	flood_fill(map, y, x + 1, height, width);
}

void	fill_player_room(char **map)
{
	int		x;
	int		y;
	int		width;
	int		height;
	bool	p_found;

	p_found = false;
	x = 0;
	y = 0;
	width = ft_strlen(map[0]);
	height = array_len((void **)map);
	while (y < height && !p_found)
	{
		x = 0;
		while (x < width && !p_found)
		{
			if (in(map[y][x], "NSEW"))
			{
				p_found = true;
				call_flood(map, y, x, height, width);
			}
			x++;
		}
		y++;
	}
}
