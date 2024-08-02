/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_parser.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bthomas <bthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 16:31:17 by bthomas           #+#    #+#             */
/*   Updated: 2024/08/02 10:56:27 by bthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	init_input(t_map_data *mapdata, char *fname)
{
	mapdata->fd = open(fname, O_RDONLY);
	if (mapdata->fd < 0)
		return (ft_printf("Error\nCould not open file\n"));
	mapdata->input = (char **)ft_calloc(32, sizeof(char *));
	if (!mapdata->input)
	{
		close(mapdata->fd);
		return (ft_printf("Error\nMalloc failure.\n"));
	}
	return (0);
}
