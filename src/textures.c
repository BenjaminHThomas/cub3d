/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okoca <okoca@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 16:16:50 by okoca             #+#    #+#             */
/*   Updated: 2024/07/31 14:41:21 by okoca            ###   ########.fr       */
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
	int			err;

	err = 0;
	texture = malloc(sizeof(t_texture) * 4);
	texture[NORTH] = create_texture(ctx, "textures/boss.xpm", &err);
	texture[SOUTH] = create_texture(ctx, "textures/psyop.xpm", &err);
	texture[WEST] = create_texture(ctx, "textures/aple.xpm", &err);
	texture[EAST] = create_texture(ctx, "textures/alpha.xpm", &err);
	ctx->textures = texture;
	return (0);
}
