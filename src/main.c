/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okoca <okoca@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/27 13:57:19 by okoca             #+#    #+#             */
/*   Updated: 2024/07/27 16:26:53 by okoca            ###   ########.fr       */
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

void	cb_mini_draw(t_ctx *ctx)
{
	void	*image;
	int		bits_per_pix;
	int		line_size;
	int		endian;
	char	*buffer;

	int	color = 0x19987f;
	image = mlx_new_image(ctx->mlx, 1024, 512);
	buffer = mlx_get_data_addr(image, &bits_per_pix, &line_size, &endian);
	printf("bits_p: %d\n", bits_per_pix);
	printf("line_size: %d\n", line_size);
	printf("endian: %d\n", endian);
	for (int y = 0; y < 512; y++)
	for (int x = 0; x < 1024; x++)
	{
		int	pixel = (y * line_size) + (x * 4);
		if (endian == 1)
		{
			buffer[pixel + 0] = (color >> 24);
			buffer[pixel + 1] = (color >> 16) & 0xFF;
			buffer[pixel + 2] = (color >> 8) & 0xFF;
			buffer[pixel + 3] = (color) & 0xFF;
		}
		else if (endian == 0)
		{
			buffer[pixel + 0] = (color & 0xFF);
			buffer[pixel + 1] = (color >> 8) & 0xFF;
			buffer[pixel + 2] = (color >> 16) & 0xFF;
			buffer[pixel + 3] = (color >> 24);
		}
	}
	(void)buffer;
	mlx_put_image_to_window(ctx->mlx, ctx->window, image, 0, 0);
	mlx_destroy_image(ctx->mlx, image);
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
