/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okoca <okoca@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 16:16:50 by okoca             #+#    #+#             */
/*   Updated: 2024/08/03 09:08:11 by okoca            ###   ########.fr       */
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

int	cb_tex_error(t_ctx *ctx, t_texture *tex)
{
	int			j;

	j = 0;
	while (j < TEXTURE_COUNT)
	{
		if (tex[j].data != NULL)
			mlx_destroy_image(ctx->mlx, tex[j].data);
		j++;
	}
	free(tex);
	return (1);
}

int	init_textures(t_ctx *ctx)
{
	t_texture	*texture;
	t_tex_path	*current;
	int			err;
	int			i;
	char		*tmp;

	i = 0;
	err = 0;
	texture = ft_calloc(sizeof(t_texture), TEXTURE_COUNT);
	while (i < TEXTURE_COUNT)
	{
		current = ctx->mapdata->tex_paths[i];
		tmp = ft_substr(current->path, 0, ft_strlen(current->path) - 1);
		texture[current->dir] = create_texture(ctx, tmp, &err);
		free(tmp);
		if (err == 1)
			return (cb_tex_error(ctx, texture));
		i++;
	}
	ctx->textures = texture;
	return (0);
}
