/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okoca <okoca@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 08:44:50 by okoca             #+#    #+#             */
/*   Updated: 2024/07/28 11:27:07 by okoca            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
* 111111111111
* 100000000001
* 100000000001
* 10P000110001
* 100000110001
* 100000000001
* 100000000001
* 100000000001
* 100000000001
* 111111111111
*/
t_map	*init_map()
{
	t_map	*map;
	int		i;

	i = 0;
	map = malloc(sizeof(t_map));
	map->player.x = 3.0f;
	map->player.y = 3.0f;
	map->player.angle = 0.0f;

	map->height = 10;
	map->width = 12;
	map->raw = ft_calloc(sizeof(char), (map->height * map->width + 1));
	while (i < map->height)
	{
		if (i == 0 || i == 9)
			ft_strcat(map->raw, "111111111111");
		else if (i == 3 || i == 4)
			ft_strcat(map->raw, "100000110001");
		else
			ft_strcat(map->raw, "100000000001");
		i++;
	}
	map->raw[i] = '\0';
	return (map);
}
