/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okoca <okoca@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/27 13:57:19 by okoca             #+#    #+#             */
/*   Updated: 2024/07/29 17:18:36 by okoca            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	cb_free_all(void *param)
{
	t_ctx	*ctx;

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

void	cb_int_put_pixel(t_img *img, t_vec vec, t_color color)
{
	int	pixel = (vec.y * img->line_size) + vec.x;

	img->buffer[pixel] = color;
}

void	cb_put_pixel(t_img *img, t_vec vec, t_color color, float shading)
{
	int	pixel = (vec.y * img->line_size) + (vec.x * 4);

	if (img->endian == 1)
	{
		img->buffer[pixel + 0] = (color >> 24);
		img->buffer[pixel + 1] = ((color >> 16) & 0xFF) * shading;
		img->buffer[pixel + 2] = ((color >> 8) & 0xFF) * shading;
		img->buffer[pixel + 3] = ((color) & 0xFF) * shading;
	}
	else if (img->endian == 0)
	{
		img->buffer[pixel + 0] = (color & 0xFF) * shading;
		img->buffer[pixel + 1] = ((color >> 8) & 0xFF) * shading;
		img->buffer[pixel + 2] = ((color >> 16) & 0xFF) * shading;
		img->buffer[pixel + 3] = (color >> 24);
	}
}

void	cb_mini_draw(t_ctx *ctx)
{
	int		color;
	t_vec	vec;
	t_player	player;

	vec.x = 0;
	vec.y = 0;
	vec.angle = 0;
	color = 0x19987f;
	player = ctx->map->player;
	float f_depth = 12.0f;
	(void)f_depth;
	(void)player;
	while (vec.x++ < SCREEN_WIDTH)
	{
		float	camera_x = 2 * vec.x / SCREEN_WIDTH - 1;
		float	ray_dir_x = player.dx + player.plane_x * camera_x;
		float	ray_dir_y = player.dy + player.plane_y * camera_x;

		int		map_x = (int)player.x;
		int		map_y = (int)player.y;

		float	side_dist_x;
		float	side_dist_y;

		double	delta_dist_x = (ray_dir_x == 0) ? 1e30 : fabs(1 / ray_dir_x);
		double	delta_dist_y = (ray_dir_y == 0) ? 1e30 : fabs(1 / ray_dir_y);
		float	perp_wall_dist;

		int		step_x;
		int		step_y;

		int		hit = 0;
		int		side;

		if (ray_dir_x < 0)
		{
			step_x = -1;
			side_dist_x = (player.x - map_x) * delta_dist_x;
		}
		else
		{
			step_x = 1;
			side_dist_x = (map_x + 1.0 - player.x) * delta_dist_x;
		}
		if (ray_dir_y < 0)
		{
			step_y = -1;
			side_dist_y = (player.y - map_y) * delta_dist_y;
		}
		else
		{
			step_y = 1;
			side_dist_y = (map_y + 1.0 - player.y) * delta_dist_y;
		}

		while (hit == 0)
		{
			if (side_dist_x < side_dist_y)
			{
				side_dist_x += delta_dist_x;
				map_x += step_x;
				side = 0;
			}
			else
			{
				side_dist_y += delta_dist_y;
				map_y += step_y;
				side = 1;
			}
			if (ctx->map->raw[map_y * ctx->map->width + map_x] == '1')
			{
				hit = 1;
				// printf("----------\nmap_x: %d\nmap_y: %d\n---------\n", map_x, map_y);
			}
		}

		if (side == 0)
			perp_wall_dist = (side_dist_x - delta_dist_x);
		else
			perp_wall_dist = (side_dist_y - delta_dist_y);

		int line_height = (int)(SCREEN_HEIGHT / perp_wall_dist);

		int draw_start = -line_height / 2 + SCREEN_HEIGHT / 2;
		if (draw_start < 0)
			draw_start = 0;
		int draw_end = line_height / 2 + SCREEN_HEIGHT / 2;
		if (draw_end >= SCREEN_HEIGHT)
			draw_end = SCREEN_HEIGHT - 1;

		color = 0x100fff;
		if (side == 1)
			color = color / 2;
		vec.y = draw_start;
		while (hit && vec.y++ < draw_end)
		{
			cb_put_pixel(ctx->img, vec, color, 1.0f);
		}


	}
	mlx_put_image_to_window(ctx->mlx, ctx->window, ctx->img->img, 0, 0);
}
// (void)perp_wall_dist;
// vec.y = 0;
// while (vec.y++ < SCREEN_HEIGHT)
// {
// 	color = 0x100fff;
// 	cb_put_pixel(ctx->img, vec, color, 1.0f);
// }



int	main(int ac, char **av)
{
	t_ctx	ctx;
	int		i;

	i = 0;
	(void)ac;
	(void)av;
	ctx.fov = M_PI / FOV;
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

