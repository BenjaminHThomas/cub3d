/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_validation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bthomas <bthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 13:04:17 by bthomas           #+#    #+#             */
/*   Updated: 2024/08/01 19:14:46 by bthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

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
	exten = ft_substr(fname, len - 4, 4);
	if (!exten)
		return (false);
	retval = false;
	if (ft_strcmp(exten, ".cub") == 0)
		retval = true;
	free(exten);
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

bool	valid_colours(t_map_data *mapdata)
{
	(void)mapdata;
	return (true);
}
