/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okoca <okoca@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 16:16:50 by okoca             #+#    #+#             */
/*   Updated: 2024/07/30 13:38:42 by okoca            ###   ########.fr       */
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
	// int			i;
	int			err;

	// i = 0;
	err = 0;
	texture = malloc(sizeof(t_texture) * 4);
	texture[NORTH] = create_texture(ctx, "textures/boss.xpm", &err);
	texture[EAST] = create_texture(ctx, "textures/psyop.xpm", &err);
	texture[SOUTH] = create_texture(ctx, "textures/aple.xpm", &err);
	texture[WEST] = create_texture(ctx, "textures/alpha.xpm", &err);
	// GOOD CODE BUT FOR TESTING PURPOSES IM GOING TO LEAVE IT OUT
	// while (i < 4)
	// {
	// 	texture[i] = create_texture(ctx, "textures/ground.xpm", &err);
	// 	if (err == 1)
	// 	{
	// 		while (i--)
	// 			mlx_destroy_image(ctx->mlx, texture[i].data);
	// 		free(texture);
	// 		return (1);
	// 	}
	// 	i++;
	// }
	ctx->textures = texture;
	return (0);
}
