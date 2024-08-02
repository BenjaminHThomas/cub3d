/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bthomas <bthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 14:05:49 by bthomas           #+#    #+#             */
/*   Updated: 2024/08/02 17:23:56 by bthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <stdio.h>

static int	read_cub(t_map_data *mapdata, char *fname)
{
	if (!valid_fname(fname))
	{
		printf("Error\nInvalid filename\n");
		return (1);
	}
	if (init_input(mapdata, fname))
		return (1);
	get_file_contents(mapdata);
	if (!mapdata->input)
	{
		printf("Error\nCould not retrieve file contents\n");
		bin_parse_data(mapdata);
		return (1);
	}
	mapdata->tex_paths = get_textures(mapdata);
	if (!mapdata->tex_paths)
	{
		printf("Error\nCould not retrieve texture paths from file.\n");
		bin_parse_data(mapdata);
		return (1);
	}
	return (0);
}

t_map_data	*parse(char **av)
{
	t_map_data	*new;
	t_map_data	mapdata;
	char		*fname;
	size_t		i;

	fname = av[1];
	if (read_cub(&mapdata, fname))
		return (NULL);
	if (get_hex_colour(&mapdata, 4) || get_hex_colour(&mapdata, 5))
	{
		bin_parse_data(&mapdata);
		return (ft_putendl_fd("Error\nIncorrect RGB values supplied.\n", 2)
			, NULL);
	}
	if (read_map(&mapdata))
	{
		bin_parse_data(&mapdata);
		return (ft_putendl_fd("Error\nCould not read map.\n", 2), NULL);
	}
	if (!valid_map(&mapdata))
		return (bin_parse_data(&mapdata), NULL);
	fill_player_room(mapdata.map);
	new = ft_calloc(1, sizeof(t_map_data));
	ft_memmove(new, &mapdata, sizeof(t_map_data));
	return (new);
}
