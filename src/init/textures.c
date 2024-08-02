/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okoca <okoca@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 16:16:50 by okoca             #+#    #+#             */
/*   Updated: 2024/08/02 17:48:09 by okoca            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_texture	create_texture(t_ctx *ctx, char *path, int *err)
{
	t_texture	new;

	new.data = mlx_xpm_file_to_image(ctx->mlx, path,
			&new.w, &new.h);
	if (!new.data)
	{
		*err = 1;
		return (new);
	}
	new.img.buffer = mlx_get_data_addr(new.data, &new.img.bits_per_pixel,
			&new.img.line_size, &new.img.endian);
	*err = 0;
	return (new);
}

int	init_textures(t_ctx *ctx)
{
	t_texture	*texture;
	t_tex_path	*current;
	int			err;
	int			i;
	int			j;
	char		*tmp;

	i = 0;
	j = 0;
	err = 0;
	texture = ft_calloc(sizeof(t_texture), TEXTURE_COUNT);
	while (i < TEXTURE_COUNT)
	{
		current = ctx->mapdata->tex_paths[i];
		tmp = ft_substr(current->path, 0, ft_strlen(current->path) - 1);
		texture[current->dir] = create_texture(ctx, tmp, &err);
		free(tmp);
		if (err == 1)
		{
			while (j < TEXTURE_COUNT)
			{
				if (texture[j].data != NULL)
					mlx_destroy_image(ctx->mlx, texture[j].data);
				j++;
			}
			free(texture);
			return (1);
		}
		i++;
	}
	ctx->textures = texture;
	return (0);
}
