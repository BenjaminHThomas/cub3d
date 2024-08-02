/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_cub.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bthomas <bthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 11:31:30 by bthomas           #+#    #+#             */
/*   Updated: 2024/08/02 18:23:51 by bthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	get_file_contents(t_map_data *mapdata)
{
	char	*line;
	int		i;

	i = 0;
	while (i < 6)
	{
		line = get_next_line(mapdata->fd);
		if (!line)
			break ;
		if (!is_empty_line(line))
			mapdata->input[i++] = line;
		else
		{
			free(line);
			line = NULL;
		}
	}
}

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

t_tex_path	**get_textures(t_map_data *mapdata)
{
	int			i;
	char		*line;
	t_tex_path	**texts;

	texts = ft_calloc((TEXTURE_COUNT + 1), sizeof(t_tex_path *));
	if (!texts)
		return (NULL);
	i = 0;
	while (i < TEXTURE_COUNT)
	{
		line = mapdata->input[i];
		texts[i] = get_texture(line);
		if (!texts[i])
			return (bin_textures(texts), NULL);
		i++;
	}
	if (i < 3)
		return (bin_textures(texts), NULL);
	return (texts);
}

static char	**get_rgb(char **split_line)
{
	char	**rgb;

	if (!split_line || !split_line[0] || !split_line[1])
		return (NULL);
	rgb = ft_split(split_line[1], ',');
	if (!rgb)
		return (NULL);
	if (array_len((void **)rgb) != 3)
		return (free_arr((void **)rgb), NULL);
	return (rgb);
}

int	get_hex_colour(t_map_data *mapdata, int idx)
{
	char			**temp_rgb;
	char			**split_line;
	unsigned char	rgb[3];
	unsigned int	hex_val;

	split_line = ft_split(mapdata->input[idx], ' ');
	if (!split_line)
		return (1);
	temp_rgb = get_rgb(split_line);
	if (!temp_rgb)
		return (1);
	rgb[0] = (unsigned char)ft_atoi(temp_rgb[0]);
	rgb[1] = (unsigned char)ft_atoi(temp_rgb[1]);
	rgb[2] = (unsigned char)ft_atoi(temp_rgb[2]);
	free_arr((void **)temp_rgb);
	hex_val = rgb_to_hex(rgb[0], rgb[1], rgb[2]);
	if (ft_strcmp(split_line[0], "F") == 0)
		mapdata->f_colour = hex_val;
	else if (ft_strcmp(split_line[0], "C") == 0)
		mapdata->c_colour = hex_val;
	else
		return (free_arr((void **)split_line), 1);
	free_arr((void **)split_line);
	return (0);
}
