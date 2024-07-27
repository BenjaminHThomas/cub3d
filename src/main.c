/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okoca <okoca@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/27 13:57:19 by okoca             #+#    #+#             */
/*   Updated: 2024/07/27 16:55:41 by okoca            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	cb_free_all(void *param)
{
	t_ctx	*ctx;

	ctx = (t_ctx *)param;
	if (ctx->mlx)
	{
		mlx_loop_end(ctx->mlx);
		if (ctx->window)
		{
			mlx_destroy_window(ctx->mlx, ctx->window);
			ctx->window = NULL;
		}
		mlx_destroy_display(ctx->mlx);
		free(ctx->mlx);
		ctx->mlx = NULL;
	}
	exit(0);
}

void	cb_put_pixel(t_img *img, t_vec vec, t_color color)
{
	int	pixel = (vec.y * img->line_size) + (vec.x * 4);
	if (img->endian == 1)
	{
		img->buffer[pixel + 0] = (color >> 24);
		img->buffer[pixel + 1] = (color >> 16) & 0xFF;
		img->buffer[pixel + 2] = (color >> 8) & 0xFF;
		img->buffer[pixel + 3] = (color) & 0xFF;
	}
	else if (img->endian == 0)
	{
		img->buffer[pixel + 0] = (color & 0xFF);
		img->buffer[pixel + 1] = (color >> 8) & 0xFF;
		img->buffer[pixel + 2] = (color >> 16) & 0xFF;
		img->buffer[pixel + 3] = (color >> 24);
	}
}

void	cb_mini_draw(t_ctx *ctx)
{
	int		color;
	t_vec	vec;
	t_img	img;

	vec.x = 0;
	vec.y = 0;
	color = 0x19987f;
	img.img = mlx_new_image(ctx->mlx, 1024, 512);
	img.buffer = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_size, &img.endian);
	while (vec.y++ < 512)
	{
		vec.x = 0;
		while (vec.x++ < 1024)
		{
			cb_put_pixel(&img, vec, color);
		}
	}
	mlx_put_image_to_window(ctx->mlx, ctx->window, img.img, 0, 0);
	mlx_destroy_image(ctx->mlx, img.img);
}

int	main(int ac, char **av)
{
	t_ctx	ctx;

	(void)ac;
	(void)av;
	ctx.mlx = mlx_init();
	ctx.window = mlx_new_window(ctx.mlx, 1024, 512, "cub3d");
	mlx_hook(ctx.window, DestroyNotify, StructureNotifyMask, cb_free_all, &ctx);
	cb_mini_draw(&ctx);
	mlx_loop(ctx.mlx);
	cb_free_all(&ctx);
}
