/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ctx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okoca <okoca@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 11:32:40 by okoca             #+#    #+#             */
/*   Updated: 2024/08/02 17:21:59 by okoca            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_ctx	cb_init_ctx(t_map_data *mapdata)
{
	t_ctx	ctx;

	ctx.window = NULL;
	ctx.mlx = NULL;
	ctx.mapdata = mapdata;
	ctx.textures = NULL;
	ft_bzero(&ctx.keys, sizeof(t_keys));
	ft_bzero(ctx.fps.time_str, 2);
	ctx.fps.frame_count = 0;
	ctx.fps.interval = 1.0f;
	ctx.fps.delta_time = 0.0f;
	gettimeofday(&ctx.fps.old_time, NULL);
	return (ctx);
}

int	cb_init_image(t_ctx *ctx)
{
	ctx->img.img = mlx_new_image(ctx->mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
	if (!ctx->img.img)
		return (1);
	ctx->img.buffer = mlx_get_data_addr(ctx->img.img, &ctx->img.bits_per_pixel,
			&ctx->img.line_size, &ctx->img.endian);
	return (0);
}

int	cb_init_mtx(t_ctx *ctx)
{
	ctx->mlx = mlx_init();
	if (!ctx->mlx)
		return (1);
	ctx->window = mlx_new_window(ctx->mlx, SCREEN_WIDTH,
			SCREEN_HEIGHT, PROG_NAME);
	if (!ctx->mlx)
	{
		cb_free_all(ctx);
		return (1);
	}
	if (cb_init_image(ctx) != 0)
	{
		cb_free_all(ctx);
		return (1);
	}
	if (init_textures(ctx) != 0)
	{
		cb_free_all(ctx);
		return (1);
	}
	ctx->map = init_map(ctx);
	return (0);
}
