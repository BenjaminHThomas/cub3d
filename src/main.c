/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okoca <okoca@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/27 13:57:19 by okoca             #+#    #+#             */
/*   Updated: 2024/07/30 13:51:43 by okoca            ###   ########.fr       */
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
		if (ctx->textures)
		{
			while (i < 4)
			{
				mlx_destroy_image(ctx->mlx, ctx->textures[i].data);
				i++;
			}
			free(ctx->textures);
		}
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

int	cb_darken_color(int color, float shade)
{
	int	new;
	int	red;
	int	green;
	int	blue;

	red = ((color >> 16) & 0xFF) * shade;
	green = ((color >> 8) & 0xFF) * shade;
	blue = (color & 0xFF) * shade;
	if (red > 255)
		red = 255;
	if (green > 255)
		green = 255;
	if (blue > 255)
		blue = 255;
	new = (red << 16) | (green << 8) | blue;
	return (new);
}


void	cb_put_pixel(t_img *img, t_vec vec, t_color color, float shading)
{
	int	pixel = (vec.y * (img->line_size / 4)) + (vec.x);
	int	*buffer = (int*)(img->buffer);

	color *= shading;
	if (buffer[pixel] != color)
		buffer[pixel] = color;

	// if (img->endian == 1)
	// {
	// 	img->buffer[pixel + 0] = (color >> 24);
	// 	img->buffer[pixel + 1] = ((color >> 16) & 0xFF) * shading;
	// 	img->buffer[pixel + 2] = ((color >> 8) & 0xFF) * shading;
	// 	img->buffer[pixel + 3] = ((color) & 0xFF) * shading;
	// }
	// else if (img->endian == 0)
	// {
	// 	img->buffer[pixel + 0] = (color & 0xFF) * shading;
	// 	img->buffer[pixel + 1] = ((color >> 8) & 0xFF) * shading;
	// 	img->buffer[pixel + 2] = ((color >> 16) & 0xFF) * shading;
	// 	img->buffer[pixel + 3] = (color >> 24);
	// }
}

void	cb_clear_image(t_ctx *ctx)
{
	t_vec	vec;

	vec.x = 0;
	while (vec.x < SCREEN_WIDTH)
	{
		vec.y = 0;
		while (vec.y < SCREEN_HEIGHT)
		{
			cb_put_pixel(ctx->img, vec, 0x000, 0.0f);
			vec.y++;
		}
		vec.x++;
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
	player = ctx->map->player;
	while (vec.x < SCREEN_WIDTH)
	{
		double	camera_x = 2 * vec.x / SCREEN_WIDTH - 1;
		double	ray_dir_x = player.dx + player.plane_x * camera_x;
		double	ray_dir_y = player.dy + player.plane_y * camera_x;

		int		map_x = (int)player.x;
		int		map_y = (int)player.y;

		double	side_dist_x;
		double	side_dist_y;

		double	delta_dist_x = (ray_dir_x == 0) ? 1e30 : fabs(1 / ray_dir_x);
		double	delta_dist_y = (ray_dir_y == 0) ? 1e30 : fabs(1 / ray_dir_y);
		double	distance_to_wall;

		int		step_x;
		int		step_y;

		int		hit = 0;
		int		side;
		int		orientation = 0;

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
				hit = 1;
		}

		if (side == 0)
			distance_to_wall = (side_dist_x - delta_dist_x);
		else
			distance_to_wall = (side_dist_y - delta_dist_y);

		int line_height = (int)(SCREEN_HEIGHT / distance_to_wall);

		int draw_start = -line_height / 2 + SCREEN_HEIGHT / 2;
		if (draw_start < 0)
			draw_start = 0;
		int draw_end = line_height / 2 + SCREEN_HEIGHT / 2;
		if (draw_end >= SCREEN_HEIGHT)
			draw_end = SCREEN_HEIGHT - 1;

		double	wall_x;
		if (side == 0)
			wall_x = player.y + distance_to_wall * ray_dir_y;
		else
			wall_x = player.x + distance_to_wall * ray_dir_x;
		wall_x -= floor(wall_x);

		if (side == 0)
		{
			if (ray_dir_x > 0)
				orientation = EAST;
			else
				orientation = WEST;
		}
		else
		{
			if (ray_dir_y > 0)
				orientation = SOUTH;
			else
				orientation = NORTH;
		}
		int tex_width = ctx->textures[orientation].w;
		int tex_height = ctx->textures[orientation].h;

		int	tex_x = (int)(wall_x * (double)tex_width);
		if ((side == 0 && ray_dir_x > 0) || (side == 1 && ray_dir_y < 0))
			tex_x = tex_width - tex_x - 1;

		double	step = (double)tex_height / line_height;
		double	tex_pos = (draw_start - SCREEN_HEIGHT / 2 + line_height / 2) * step;

		int		*arr = (int*)ctx->textures[orientation].img.buffer;
		int		tex_line_size = ctx->textures[orientation].img.line_size / 4;
		float	shading = 0.0f;


		vec.y = 0;
		while (vec.y < SCREEN_HEIGHT)
		{
			if (vec.y >= draw_start && vec.y <= draw_end) // wall
			{
				int	tex_y = (int)tex_pos % tex_height;
				tex_pos += step;

				color = arr[(tex_y * tex_line_size + tex_x)];
				if (side == 1)
					shading = 1.5f;
				else
					shading = 1.0f;
				color = cb_darken_color(color, shading);
				cb_put_pixel(ctx->img, vec, color, 1.0f);
			}
			else if (vec.y < draw_start) // ceilling
			{
				color = 0x70129a;
				cb_put_pixel(ctx->img, vec, color, 1.0f);
			}
			else if (vec.y > draw_end) // floor
			{
				color = 0x0fa0b9;
				cb_put_pixel(ctx->img, vec, color, 1.0f);
			}
			vec.y++;
		}
		vec.x++;
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
	if (check_args(av, av) != 0)
		return (1);
	if (parsing(av[1], &ctx) != 0)
		return (1);
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
		mlx_destroy_display(ctx.mlx);
		free(ctx.mlx);
		return (1);
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

