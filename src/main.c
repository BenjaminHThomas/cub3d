/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okoca <okoca@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/27 13:57:19 by okoca             #+#    #+#             */
/*   Updated: 2024/07/28 16:24:38 by okoca            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	cb_free_all(void *param)
{
	t_ctx	*ctx;
	int		i;

	i = 0;
	ctx = (t_ctx *)param;
	if (ctx->map && ctx->map->raw)
	{
		free(ctx->map->raw);
		free(ctx->map);
	}
	if (ctx->mlx)
	{
		if (ctx->textures.data)
			mlx_destroy_image(ctx->mlx, ctx->textures.data);
		if (ctx->img)
		{
			mlx_destroy_image(ctx->mlx, ctx->img->img);
			free(ctx->img);
		}
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
	t_vec2	player;

	vec.x = 0;
	vec.y = 0;
	vec.angle = 0;
	color = 0x19987f;
	player = ctx->map->player;
	float f_depth = 12.0f;
	while (vec.y++ < SCREEN_HEIGHT)
	{
		vec.x = 0;
		while (vec.x++ < SCREEN_WIDTH)
		{
			int	hit_wall = 0;
			float f_ray_angle = (player.angle - ctx->fov / 2.0f)
				+ ((float)vec.x / (float)SCREEN_WIDTH) * ctx->fov;
			float f_distance_to_wall = 0.0f;
			float f_eye_x = sinf(f_ray_angle);
			float f_eye_y = cosf(f_ray_angle);

			while (!hit_wall && f_distance_to_wall < f_depth)
			{
				f_distance_to_wall += PRECISION;

				int	n_test_x = (int)(player.x + f_eye_x * f_distance_to_wall);
				int	n_test_y = (int)(player.y + f_eye_y * f_distance_to_wall);
				if (n_test_x < 0 || n_test_x >= 12 || n_test_y < 0 || n_test_y >= 12)
				{
					hit_wall = 1;
					f_distance_to_wall = f_depth;
				}
				else
				{
					if (ctx->map->raw[n_test_y * ctx->map->width + n_test_x] == '1')
						hit_wall = 1;
				}
			}

			int n_ceilling = (float)(SCREEN_HEIGHT / 2.0f) - SCREEN_HEIGHT / ((float)f_distance_to_wall);
			int n_floor = SCREEN_HEIGHT - n_ceilling;

			if (vec.y < n_ceilling)
			{
				color = 0x1affff;
				cb_put_pixel(ctx->img, vec, color);
			}
			else if (vec.y > n_ceilling && vec.y <= n_floor)
			{
				if (f_distance_to_wall < 4)
					color = 0xaf00ef;
				else if (f_distance_to_wall < 7)
					color = 0xa000ff;
				else
					color = 0x7010ff;
				cb_put_pixel(ctx->img, vec, color);
			}
			else
			{
				color = 0x100fff;
				cb_put_pixel(ctx->img, vec, color);
			}
		}
	}
	mlx_put_image_to_window(ctx->mlx, ctx->window, ctx->img->img, 0, 0);
}

int	main(int ac, char **av)
{
	t_ctx	ctx;
	int		i;

	i = 0;
	(void)ac;
	(void)av;
	ctx.fov = M_PI / 4.0f;
	printf("PI: %f\n", ctx.fov);
	ctx.map = init_map();
	while (i < ctx.map->height)
	{
		printf("%.12s\n", &(ctx.map->raw[i * ctx.map->width]));
		i++;
	}
	ctx.mlx = mlx_init();
	if (init_textures(&ctx) != 0)
	{
		printf("entered this\n");
		free(ctx.map->raw);
		free(ctx.map);
		free(ctx.mlx);
	}
	ctx.img = malloc(sizeof(t_img));
	ctx.img->img = mlx_new_image(ctx.mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
	ctx.img->buffer = mlx_get_data_addr(ctx.img->img, &ctx.img->bits_per_pixel, &ctx.img->line_size, &ctx.img->endian);
	ctx.window = mlx_new_window(ctx.mlx, SCREEN_WIDTH, SCREEN_HEIGHT, "cub3d");
	mlx_hook(ctx.window, DestroyNotify, StructureNotifyMask, cb_free_all, &ctx);
	mlx_hook(ctx.window, KeyPress, KeyPressMask, cb_handle_key, &ctx);
	cb_mini_draw(&ctx);
	mlx_loop(ctx.mlx);
	cb_free_all(&ctx);
}
