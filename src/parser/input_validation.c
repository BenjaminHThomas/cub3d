/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_validation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bthomas <bthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 13:04:17 by bthomas           #+#    #+#             */
/*   Updated: 2024/08/03 10:08:21 by bthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool	valid_fname(char *fname)
{
	bool	retval;
	size_t	len;
	char	*exten;

	if (!fname)
		return (false);
	len = ft_strlen(fname);
	if (len < 5)
		return (false);
	exten = ft_strrchr(fname, '.');
	retval = false;
	if (ft_strcmp(exten, ".cub") == 0)
		retval = true;
	return (retval);
}

bool	valid_textures(t_map_data *mapdata)
{
	bool	north;
	bool	south;
	bool	east;
	bool	west;
	int		i;

	north = false;
	south = false;
	east = false;
	west = false;
	i = 0;
	while (i < 3)
	{
		if (mapdata->tex_paths[i]->dir == NORTH)
			north = true;
		else if (mapdata->tex_paths[i]->dir == SOUTH)
			south = true;
		else if (mapdata->tex_paths[i]->dir == EAST)
			east = true;
		else if (mapdata->tex_paths[i]->dir == WEST)
			west = true;
		i++;
	}
	return (north && south && east && west);
}

static bool	valid_map_chars(t_map_data *mapdata, char **map)
{
	bool	player_found;
	size_t	x;
	size_t	y;

	player_found = false;
	y = -1;
	while (map[++y])
	{
		x = -1;
		while (map[y][++x])
		{
			if (!in(map[y][x], "10NSEW"))
				return (false);
			if (!player_found && in(map[y][x], "NSEW"))
			{
				player_found = true;
				mapdata->player_dir = char_to_dir(map[y][x]);
				mapdata->player_pos.x = (double)x;
				mapdata->player_pos.y = (double)y;
			}
			else if (player_found && in(map[y][x], "NSEW"))
				return (false);
		}
	}
	return (player_found);
}

static bool	map_border_valid(char **map)
{
	size_t	len;
	size_t	i;
	size_t	arrlen;

	if (!all_are_c('1', map[0]))
		return (false);
	len = ft_strlen(map[0]);
	arrlen = arr_len((void **)map);
	if (len * arrlen > 2500)
		return (false);
	i = 0;
	while (map[i])
	{
		if (map[i][0] != '1' || map[i][len - 1] != '1')
			return (false);
		i++;
	}
	i--;
	if (!all_are_c('1', map[i]))
		return (false);
	return (true);
}

/*
	- No zeroes on the border
	- Only one direction character
	- Only 1, 0, (N,S,E,W)
	- player not surrounded by 1's on all sides
*/
bool	valid_map(t_map_data *mapdata)
{
	char	**map;
	size_t	x;
	size_t	y;
	bool	retval;

	if (!mapdata->map || !(*mapdata->map))
		return (false);
	map = mapdata->map;
	if (!map_border_valid(map))
	{
		ft_putendl_fd("Error\nMap border invalid.", 2);
		return (false);
	}
	if (!valid_map_chars(mapdata, map))
	{
		ft_putendl_fd("Error\nInvalid map characters.", 2);
		return (false);
	}
	x = (size_t)mapdata->player_pos.x;
	y = (size_t)mapdata->player_pos.y;
	retval = (!(map[y - 1][x] == 1
				&& map[y + 1][x] == 1
				&& map[y][x - 1] == 1
				&& map[y][x + 1] == 1));
	return (retval);
}
