/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okoca <okoca@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/27 13:57:19 by okoca             #+#    #+#             */
/*   Updated: 2024/07/29 16:46:24 by okoca            ###   ########.fr       */
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
	t_vec2	player;

	vec.x = 0;
	vec.y = 0;
	vec.angle = 0;
	color = 0x19987f;
	player = ctx->map->player;
	float	plane_x = 0;
	float	plane_y = 0.66;
	float f_depth = 12.0f;
	(void)f_depth;
	(void)player;
	while (vec.x++ < SCREEN_WIDTH)
	{

		float	camera_x = 2 * vec.x / SCREEN_WIDTH - 1;
		float	ray_dir_x = player.dx + plane_x * camera_x;
		float	ray_dir_y = player.dy + plane_y * camera_x;

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
			if (ctx->map->raw[map_x * map_y] == '1')
				hit = 1;
			if (side == 0)
				perp_wall_dist = (side_dist_x - delta_dist_x);
			else
				perp_wall_dist = (side_dist_y - delta_dist_y);
			(void)perp_wall_dist;
		}

		vec.y = 0;
		while (vec.y++ < SCREEN_HEIGHT)
		{
			color = 0x100fff;
			cb_put_pixel(ctx->img, vec, color, 1.0f);
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

// void	cb_mini_draw(t_ctx *ctx)
// {
// 	int		color;
// 	t_vec	vec;
// 	t_vec2	player;

// 	vec.x = 0;
// 	vec.y = 0;
// 	vec.angle = 0;
// 	color = 0x19987f;
// 	player = ctx->map->player;
// 	float f_depth = 12.0f;

// 	while (vec.x++ < SCREEN_WIDTH)
// 	{
// 		int	hit_wall = 0;
// 		float f_ray_angle = (player.angle - ctx->fov / 2.0f)
// 			+ ((float)vec.x / (float)SCREEN_WIDTH) * ctx->fov;
// 		float	f_distance_to_wall = 0.0f;
// 		float	f_eye_x = sinf(f_ray_angle);
// 		float	f_eye_y = cosf(f_ray_angle);
// 		float	f_sample_x = 0.0f;
// 		float	f_sample_y = 0.0f;
// 		float	wall_x = 0.0f;
// 		int		orientation;

// 		while (!hit_wall && f_distance_to_wall < f_depth)
// 		{
// 			f_distance_to_wall += PRECISION;

// 			int	n_test_x = (int)(player.x + f_eye_x * f_distance_to_wall);
// 			int	n_test_y = (int)(player.y + f_eye_y * f_distance_to_wall);
// 			if (n_test_x < 0 || n_test_x >= 12 || n_test_y < 0 || n_test_y >= 12)
// 			{
// 				hit_wall = 1;
// 				f_distance_to_wall = f_depth;
// 			}
// 			else
// 			{
// 				if (ctx->map->raw[n_test_y * ctx->map->width + n_test_x] == '1')
// 				{
// 					hit_wall = 1;

// 					// float f_block_mid_x = (float)n_test_x + 0.5f;
// 					// float f_block_mid_y = (float)n_test_y + 0.5f;

// 					float f_test_point_x = player.x + f_eye_x * f_distance_to_wall;
// 					float f_test_point_y = player.y + f_eye_y * f_distance_to_wall;

// 					// float f_test_angle = atan2f((f_test_point_y - f_block_mid_y), (f_test_point_x - f_block_mid_x));

// 					// if (n_test_x == (int)player.x + f_eye_x || n_test_x == (int)player.x - f_eye_x)
// 					// {
// 					// 	orientation = 1;
// 					// 	wall_x = player.y + f_eye_y * f_distance_to_wall;
// 					// }
// 					// else
// 					// {
// 					// 	orientation = 0;
// 					// 	wall_x = player.x + f_eye_x * f_distance_to_wall;
// 					// }
// 					// wall_x -= floorf(wall_x);

// 					// if (f_test_angle >= M_PI * 0.25f && f_test_angle < M_PI * 0.25f)
// 					// 	f_sample_x = f_test_point_y - (float)n_test_y;
// 					// if (f_test_angle >= M_PI * 0.25f && f_test_angle < M_PI * 0.75f)
// 					// 	f_sample_x = f_test_point_x - (float)n_test_x;
// 					// if (f_test_angle < M_PI * 0.25f && f_test_angle >= M_PI * 0.75f)
// 					// 	f_sample_x = f_test_point_x - (float)n_test_x;
// 					// if (f_test_angle >= M_PI * 0.75f || f_test_angle < M_PI * 0.75f)
// 					// 	f_sample_x = f_test_point_y - (float)n_test_y;

// 					float	block_edge_x = n_test_x + (f_eye_x > 0 ? 1 : 0);
// 					float	block_edge_y = n_test_y + (f_eye_y > 0 ? 1 : 0);
// 					(void)block_edge_y;

// 					float	dx = f_test_point_x - n_test_x;
// 					float	dy = f_test_point_y - n_test_y;

// 					if (fabsf(f_test_point_x - block_edge_x) < 0.01f)
// 					{
// 						orientation = f_eye_x > 0 ? 0 : 1;
// 						wall_x = dy;
// 					}
// 					else
// 					{
// 						orientation = f_eye_y > 0 ? 2 : 3;
// 						wall_x = dx;
// 					}

// 					// if (fabs(dx) > fabs(dy))
// 					// {
// 					// 	orientation = (f_eye_x > 0) ? 0 : 1;
// 					// 	wall_x = f_test_point_y - n_test_y;
// 					// }
// 					// else
// 					// {
// 					// 	orientation = (f_eye_y > 0) ? 2 : 3;
// 					// 	wall_x = f_test_point_x - n_test_x;
// 					// }
// 					// wall_x -= floorf(wall_x);


// 					// if (cosf(f_ray_angle) > 0.0001 || cosf(f_ray_angle) < -0.001)
// 					// {
// 					// 	wall_x = player.y + f_distance_to_wall * sinf(f_ray_angle);
// 					// }
// 					// else
// 					// {
// 					// 	wall_x = player.x + f_distance_to_wall + cosf(f_ray_angle);
// 					// }
// 					// wall_x -= floorf(wall_x);
// 				}
// 			}
// 		}

// 		int n_ceilling = (float)(SCREEN_HEIGHT / 2.0f) - SCREEN_HEIGHT / ((float)f_distance_to_wall);
// 		int n_floor = SCREEN_HEIGHT - n_ceilling;

// 		vec.y = 0;
// 		while (vec.y++ < SCREEN_HEIGHT)
// 		{
// 			if (vec.y < n_ceilling) // ceilling
// 			{
// 				color = 0x1affff;
// 				cb_put_pixel(ctx->img, vec, color, 1.0f);
// 			}
// 			else if (vec.y > n_ceilling && vec.y <= n_floor) // wall is here
// 			{
// 				f_sample_y = ((float)vec.y - (float)n_ceilling) / ((float)n_floor - (float)n_ceilling);

// 				// int *arr = (int*)ctx->textures.img.buffer;
// 				(void)f_sample_x;
// 				(void)f_sample_y;
// 				(void)wall_x;

// 				// if (orientation == 1 || orientation == 3)
// 				// 	wall_x = 1.0f - wall_x;

// 				// if (orientation == 1 && f_eye_x > 0)
// 				// 	wall_x = 1.0f - wall_x;
// 				// if (orientation == 0 && f_eye_y < 0)
// 				// 	wall_x = 1.0f - wall_x;

// 				// int	tex_x = (int)(wall_x * ctx->textures.w) % ctx->textures.w;
// 				// int	tex_x = (int)(f_sample_x * ctx->textures.w) % ctx->textures.w;
// 				// int	tex_y = (int)(f_sample_y * ctx->textures.h) % ctx->textures.h;
// 				switch(orientation)
// 				{
// 					case 0: color = 0xFF0000; break; // Red for west-facing walls
// 					case 1: color = 0x00FF00; break; // Green for east-facing walls
// 					case 2: color = 0x0000FF; break; // Blue for north-facing walls
// 					case 3: color = 0xFFFF00; break; // Yellow for south-facing walls
// 					default: color = 0xFFFFFF; break; // White for unknown orientation
// 				}
// 				float shading = 1.0f - (f_distance_to_wall / f_depth);
// 				// int color = arr[(tex_y * (ctx->textures.img.line_size / 4) + tex_x)];

// 				cb_put_pixel(ctx->img, vec, color, shading);
// 			}
// 			else // floor
// 			{
// 				color = 0x100fff;
// 				cb_put_pixel(ctx->img, vec, color, 1.0f);
// 			}
// 		}
// 	}
// 	mlx_put_image_to_window(ctx->mlx, ctx->window, ctx->img->img, 0, 0);
// }