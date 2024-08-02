/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bthomas <bthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 16:27:36 by bthomas           #+#    #+#             */
/*   Updated: 2024/08/02 18:44:22 by bthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	get_map(t_map_data *mapdata)
{
	char	*line;
	int		size;
	int		i;

	size = 32;
	i = 6;
	while (i < size)
	{
		line = get_next_line(mapdata->fd);
		if (!line)
			break ;
		if (i == 6 && is_empty_line(line))
		{
			free(line);
			continue ;
		}
		else if (is_empty_line(line))
			return (free(line));
		else
			mapdata->input[i++] = line;
		if (i == size - 1)
			if (resize_arr(&mapdata->input, &size))
				return ;
	}
}

static char	*get_map_row(char *maprow, size_t max)
{
	size_t	input_len;
	size_t	i;
	char	*row;

	row = (char *)malloc(max + 1);
	if (!row)
		return (NULL);
	input_len = ft_strlen(maprow);
	i = 0;
	while (i < input_len && maprow[i])
	{
		if (maprow[i] == '\n')
			break ;
		if (is_space(maprow[i]))
			row[i] = '1';
		else
			row[i] = maprow[i];
		i++;
	}
	while (i < max - 1)
		row[i++] = '1';
	row[i] = 0;
	return (row);
}

int	read_map(t_map_data *mapdata)
{
	int		i;
	int		j;
	int		size;
	size_t	max_len;

	max_len = get_max_map_len(mapdata);
	size = 32;
	i = 6;
	j = 0;
	mapdata->map = (char **)ft_calloc(size, sizeof(char *));
	if (!mapdata->map)
		return (1);
	while (mapdata->input[i])
	{
		mapdata->map[j] = get_map_row(mapdata->input[i], max_len);
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
