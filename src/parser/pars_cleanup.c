/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_cleanup.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bthomas <bthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 12:05:13 by bthomas           #+#    #+#             */
/*   Updated: 2024/08/02 17:05:20 by bthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	free_arr(void **arr)
{
	size_t	i;

	if (!arr || !*arr)
		return ;
	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		arr[i] = NULL;
		i++;
	}
	free(arr);
	arr = NULL;
}

void	bin_textures(t_tex_path **texts)
{
	size_t	i;

	if (!texts)
		return ;
	i = 0;
	while (texts[i])
	{
		if (texts[i]->path)
		{
			free(texts[i]->path);
			texts[i]->path = NULL;
		}
		free(texts[i]);
		texts[i] = NULL;
		i++;
	}
	free(texts);
	texts = NULL;
	return ;
}

void	bin_parse_data(t_map_data *mapdata)
{
	if (mapdata->input)
		free_arr((void **)mapdata->input);
	if (mapdata->map)
		free_arr((void **)mapdata->map);
	if (mapdata->tex_paths)
		bin_textures(mapdata->tex_paths);
}
