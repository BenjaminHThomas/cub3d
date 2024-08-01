/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_validation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bthomas <bthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 13:04:17 by bthomas           #+#    #+#             */
/*   Updated: 2024/08/01 13:51:31 by bthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	init_input(t_map_data *mapdata, char *fname)
{
	mapdata->fd = open(fname, O_RDONLY);
	if (mapdata->fd < 0)
		return (1);
	mapdata->input = (char **)ft_calloc(32, sizeof(char *));
	if (!mapdata->input)
	{
		close(mapdata->fd);
		return (1);
	}
	return (0);
}

//check file name
bool	is_valid_fname(char *fname)
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

//read whole file
void	get_file_contents(t_map_data *mapdata, char *fname)
{
	char	*line;
	size_t	i;
	int		size;

	size = 32;
	i = -1;
	while (++i < size)
	{
		if (i == size - 1)
			if (resize_arr(&mapdata->input, &size))
				return (free_arr(mapdata->input));
		line = get_next_line(mapdata->fd);
		if (!line)
			break ;
		if (!is_empty_line(line))
			mapdata->input[i] = line;
		else
		{
			free(line);
			line = NULL;
		}
	}
}

//skip empty lines
//store in struct
