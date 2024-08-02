/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okoca <okoca@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 14:05:49 by bthomas           #+#    #+#             */
/*   Updated: 2024/08/02 16:22:58 by okoca            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <stdio.h>

t_map_data	*parse(int ac, char **av)
{
	t_map_data	mapdata;
	char		*fname;
	size_t		i;

	(void)ac;
	fname = av[1];
	if (!valid_fname(fname))
	{
		printf("Error\nInvalid filename\n");
		return (NULL);
	}
	if (init_input(&mapdata, fname))
		return (NULL);
	get_file_contents(&mapdata);
	if (!mapdata.input)
	{
		printf("Error\nCould not retrieve file contents\n");
		return (NULL);
	}
	mapdata.tex_paths = get_textures(&mapdata);
	if (!mapdata.tex_paths)
	{
		printf("Error\nCould not retrieve texture paths from file.\n");
		return (NULL);
	}
	if (get_hex_colour(&mapdata, 4) || get_hex_colour(&mapdata, 5))
	{
		printf("Error\nIncorrect RGB values supplied.\n");
		return (NULL);
	}
	printf("Floor colour: %x\n", mapdata.f_colour);
	printf("Ceiling colour: %x\n", mapdata.c_colour);
	if (read_map(&mapdata))
	{
		printf("Error\nCould not read in map.\n");
		return (NULL);
	}
	if (!valid_map(&mapdata))
		return (NULL);
	fill_player_room(mapdata.map);
	i = -1;
	t_map_data	*new = ft_calloc(1, sizeof(t_map_data));
	ft_memmove(new, &mapdata, sizeof(t_map_data));
	return (new);
}
