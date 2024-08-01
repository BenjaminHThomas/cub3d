/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_cub.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bthomas <bthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 11:31:30 by bthomas           #+#    #+#             */
/*   Updated: 2024/08/01 14:03:48 by bthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static t_tex_path	*get_texture(char *line)
{
	char		**split_line;
	t_tex_path	*retval;

	split_line = ft_split(line, ' ');
	if (!split_line || !split_line[1])
		return (free_arr(split_line), NULL);
	retval = malloc(sizeof(t_tex_path));
	if (!retval)
		return (free_arr(split_line), NULL);
	if (ft_strcmp(split_line[0], "NO") == 0)
		retval->dir = NORTH;
	else if (ft_strcmp(split_line[0], "SO") == 0)
		retval->dir = SOUTH;
	else if (ft_strcmp(split_line[0], "WE") == 0)
		retval->dir = WEST;
	else if (ft_strcmp(split_line[0], "EA") == 0)
		retval->dir = EAST;
	else
		return (free_arr(split_line), NULL);
	retval->path = ft_strdup(split_line[1]);
	free_arr(split_line);
	if (!retval->path)
		return (free(retval), NULL);
	return (retval);
}

t_tex_path	**get_textures(t_map_data *map_data, char *f_name)
{
	int			i;
	char		*line;
	t_tex_path	**texts;
	int			fd;

	fd = open(f_name, O_RDONLY);
	if (fd < 0)
		return (NULL);
	texts = malloc(4 * sizeof(t_tex_path *));
	if (!texts)
		return (NULL);
	i = 0;
	while (i < 4)
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

int	main(void)
{
	t_map_data	map_data;

	map_data.tex_paths = get_textures(&map_data, "maps/test.cub");
}
