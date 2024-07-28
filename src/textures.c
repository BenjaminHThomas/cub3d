/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okoca <okoca@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 16:16:50 by okoca             #+#    #+#             */
/*   Updated: 2024/07/28 17:04:13 by okoca            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	init_textures(t_ctx *ctx)
{
	t_texture	*texture;

	texture = &ctx->textures;
	// ctx->textures.img.img
	// ctx.img->buffer = mlx_get_data_addr(ctx.img->img, &ctx.img->bits_per_pixel, &ctx.img->line_size, &ctx.img->endian);
	texture->data = mlx_xpm_file_to_image(ctx->mlx, "textures/ground.xpm",
			&texture->w, &texture->h);
	texture->img.buffer = mlx_get_data_addr(texture->data, &texture->img.bits_per_pixel,
			&texture->img.line_size, &texture->img.endian);
	if (!ctx->textures.data)
		return (1);
	return (0);
}
