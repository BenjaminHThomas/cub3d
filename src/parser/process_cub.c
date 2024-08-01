/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_cub.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bthomas <bthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 11:31:30 by bthomas           #+#    #+#             */
/*   Updated: 2024/08/01 16:16:22 by bthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static t_tex_path	*get_texture(char *line)
{
	char		**split_line;
	t_tex_path	*retval;

	split_line = ft_split(line, ' ');
	if (!split_line || !split_line[1])
		return (free_arr((void **)split_line), NULL);
	retval = malloc(sizeof(t_tex_path));
	if (!retval)
		return (free_arr((void **)split_line), NULL);
	if (ft_strcmp(split_line[0], "NO") == 0)
		retval->dir = NORTH;
	else if (ft_strcmp(split_line[0], "SO") == 0)
		retval->dir = SOUTH;
	else if (ft_strcmp(split_line[0], "WE") == 0)
		retval->dir = WEST;
	else if (ft_strcmp(split_line[0], "EA") == 0)
		retval->dir = EAST;
	else
		return (free_arr((void **)split_line), NULL);
	retval->path = ft_strdup(split_line[1]);
	free_arr((void **)split_line);
	if (!retval->path)
		return (free(retval), NULL);
	return (retval);
}

t_tex_path	**get_textures(t_map_data *map_data)
{
	int			i;
	char		*line;
	t_tex_path	**texts;

	texts = malloc(TEXTURE_COUNT * sizeof(t_tex_path *));
	if (!texts)
		return (NULL);
	i = 0;
	while (i < TEXTURE_COUNT)
	{
		line = map_data->input[i];
		texts[i] = get_texture(line);
		if (!texts[i])
			return (bin_textures(texts), NULL);
		i++;
	}
	if (i < 3)
		return (bin_textures(texts), NULL);
	return (texts);
}
