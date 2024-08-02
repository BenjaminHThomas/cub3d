/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_parser.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bthomas <bthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 16:31:17 by bthomas           #+#    #+#             */
/*   Updated: 2024/08/02 17:28:12 by bthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	init_input(t_map_data *mapdata, char *fname)
{
	mapdata->fd = open(fname, O_RDONLY);
	if (mapdata->fd < 0)
	{
		ft_putendl_fd("Error\nCould not open file", 2);
		return (1);
	}
	mapdata->input = (char **)ft_calloc(32, sizeof(char *));
	if (!mapdata->input)
	{
		close(mapdata->fd);
		ft_putendl_fd("Error\nMalloc failure.", 2);
		return (1);
	}
	return (0);
}
