/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bthomas <bthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 16:27:36 by bthomas           #+#    #+#             */
/*   Updated: 2024/08/02 10:55:33 by bthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	read_map(t_map_data *mapdata)
{
	int		i;
	int		j;
	int		size;

	size = 32;
	i = 6;
	j = 0;
	mapdata->map = (char **)ft_calloc(size, sizeof(char *));
	if (!mapdata->map)
		return (1);
	while (mapdata->input[i])
	{
		mapdata->map[j] = ft_strdup(mapdata->input[i]);
		if (!mapdata->map[j])
			return (1);
		j++;
		i++;
		if (j == size - 1)
			if (resize_arr(&mapdata->map, &size))
				return (1);
	}
	return (0);
}
