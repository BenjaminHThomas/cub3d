/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okoca <okoca@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 16:16:50 by okoca             #+#    #+#             */
/*   Updated: 2024/08/01 14:46:17 by okoca            ###   ########.fr       */
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
	// t_map_data	map_data;
	// t_tex_path	current;
	int			err;
	int			i;

	i = 0;
	err = 0;
	texture = malloc(sizeof(t_texture) * 4);
	// map_data = ctx->map_data;
	// while (i < TEXTURE_COUNT)
	// {
	// 	texture[i].data = NULL;
	// }
	texture[NORTH] = create_texture(ctx, "textures/boss.xpm", &err);
	texture[SOUTH] = create_texture(ctx, "textures/psyop.xpm", &err);
	texture[WEST] = create_texture(ctx, "textures/aple.xpm", &err);
	texture[EAST] = create_texture(ctx, "textures/alpha.xpm", &err);
	// while (i < TEXTURE_COUNT)
	// {
	// 	current = map_data.tex_paths[i];
	// 	texture[current.dir] = create_texture(ctx, current.path, &err);
	// 	if (err == 1)
	// 	{
	// 		while (i--)
	// 		{
	// 		}
	// 	}
	// 	i++;
	// }
	ctx->textures = texture;
	return (0);
}
