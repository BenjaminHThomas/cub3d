/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okoca <okoca@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 14:38:59 by bthomas           #+#    #+#             */
/*   Updated: 2024/08/02 16:16:13 by okoca            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	flood_fill(char **map, int y, int x, t_vec lims)
{
	int	height;
	int	width;

	height = (int)lims.y;
	width = (int)lims.x;
	if (y <= 0 || y >= height || x <= 0 || x >= width
		|| in(map[y][x], "NSEW1Z"))
		return ;
	map[y][x] = 'Z';
	flood_fill(map, y - 1, x, lims);
	flood_fill(map, y + 1, x, lims);
	flood_fill(map, y, x - 1, lims);
	flood_fill(map, y, x + 1, lims);
}

static void	call_flood(char	**map, int y, int x)
{
	t_vec	lims;

	lims.x = (double)ft_strlen(map[0]);
	lims.y = (double)array_len((void **)map);
	flood_fill(map, y - 1, x, lims);
	flood_fill(map, y + 1, x, lims);
	flood_fill(map, y, x - 1, lims);
	flood_fill(map, y, x + 1, lims);
}

void	fill_player_room(char **map)
{
	int		x;
	int		y;
	bool	p_found;

	p_found = false;
	x = 0;
	y = 0;
	while (map[y] && !p_found)
	{
		x = 0;
		while (map[y][x] && !p_found)
		{
			if (in(map[y][x], "NSEW"))
			{
				p_found = true;
				call_flood(map, y, x);
			}
			x++;
		}
		y++;
	}
}
