/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bthomas <bthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 14:05:49 by bthomas           #+#    #+#             */
/*   Updated: 2024/08/02 13:35:01 by bthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include <stdio.h>

int	main(int ac, char **av)
{
	t_map_data	mapdata;
	char		*fname;
	size_t		i;

	(void)ac;
	fname = av[1];
	if (!valid_fname(fname))
		return (printf("Error\nInvalid filename\n"));
	if (init_input(&mapdata, fname))
		return (1);
	get_file_contents(&mapdata);
	if (!mapdata.input)
		return (printf("Error\nCould not retrieve file contents\n"));
	mapdata.tex_paths = get_textures(&mapdata);
	if (!mapdata.tex_paths)
		return (printf("Error\nCould not retrieve "
				"texture paths from file.\n"));
	if (get_hex_colour(&mapdata, 4) || get_hex_colour(&mapdata, 5))
		return (printf("Error\nIncorrect RGB values supplied.\n"));
	printf("Floor colour: %x\n", mapdata.f_colour);
	printf("Ceiling colour: %x\n", mapdata.c_colour);
	if (read_map(&mapdata))
		return (printf("Error\nCould not read in map.\n"));
	i = -1;
	while (mapdata.map[++i])
		printf("%s\n", mapdata.map[i]);
}
