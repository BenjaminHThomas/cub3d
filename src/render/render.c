/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okoca <okoca@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 15:30:20 by okoca             #+#    #+#             */
/*   Updated: 2024/07/31 22:12:37 by okoca            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

inline int	cb_clamp(int color)
{
	if (color > 255)
		return (255);
	return (color);
}

inline int	cb_darken_color(int color, float shade)
{
	int	new;
	int	red;
	int	green;
	int	blue;

	red = cb_clamp(((color >> 16) & 0xFF) * shade);
	green = cb_clamp(((color >> 8) & 0xFF) * shade);
	blue = cb_clamp((color & 0xFF) * shade);
	new = (red << 16) | (green << 8) | blue;
	return (new);
}

inline void	cb_put_pixel(t_img *img, t_vecint vec, t_color color, float shading)
{
	int	pixel;
	int	*buffer;

	pixel = (vec.y * (img->line_size / 4)) + (vec.x);
	buffer = (int *)img->buffer;
	color *= shading;
	if (buffer[pixel] != color)
		buffer[pixel] = color;
}

inline void	cb_draw_data(t_ctx *ctx)
{
	t_renderer	*rd;
	t_raytracer	rt;

	rt = ctx->raytracer;
	rd = &ctx->renderer;
	rd->line_height = (int)(SCREEN_HEIGHT / rt.distance_to_wall);
	rd->draw_start = -rd->line_height / 2 + SCREEN_HEIGHT / 2;
	if (rd->draw_start < 0)
		rd->draw_start = 0;
	rd->draw_end = rd->line_height / 2 + SCREEN_HEIGHT / 2;
	if (rd->draw_end >= SCREEN_HEIGHT)
		rd->draw_end = SCREEN_HEIGHT - 1;

	if (rt.side == 0)
		rd->wall_x = ctx->map.player.y + rt.distance_to_wall * rt.ray_dir.y;
	else
		rd->wall_x = ctx->map.player.x + rt.distance_to_wall * rt.ray_dir.x;
	rd->wall_x -= floor(rd->wall_x);
}

int	cb_mini_draw(void *data)
{
	int			color;
	t_ctx		*ctx;
	t_raytracer	*rt;
	t_renderer	*rd;
	t_texture	texture;

	ctx = (t_ctx *)data;
	rt = &ctx->raytracer;
	rd = &ctx->renderer;
	rt->vec.x = 0;
	rt->vec.y = 0;
	while (rt->vec.x < SCREEN_WIDTH)
	{
		cb_rt_set(ctx);
		cb_side_step(ctx);
		cb_check_hit(ctx);
		cb_wall_dist(ctx);
		cb_draw_data(ctx);

		texture = ctx->textures[rt->orientation];
		int tex_width = texture.w;
		int tex_height = texture.h;

		int	tex_x = (int)(rd->wall_x * (double)tex_width);
		if ((rt->side == 0 && rt->ray_dir.x > 0) || (rt->side == 1 && rt->ray_dir.y < 0))
			tex_x = tex_width - tex_x - 1;

		double	tex_step = (double)tex_height / rd->line_height;
		double	tex_pos = (rd->draw_start - SCREEN_HEIGHT / 2 + rd->line_height / 2) * tex_step;

		int		*arr = (int*)texture.img.buffer;
		int		tex_line_size = texture.img.line_size / 4;
		float	shading = 1.0f;

		rt->vec.y = 0;
		while (rt->vec.y < SCREEN_HEIGHT && rt->vec.y < rd->draw_start)
		{
				cb_put_pixel(&ctx->img, rt->vec, CEILLING_COLOR, 1.0f);
				rt->vec.y++;
		}
		while (rt->vec.y < SCREEN_HEIGHT && rt->vec.y >= rd->draw_start && rt->vec.y <= rd->draw_end)
		{
			int	tex_y = (int)tex_pos % tex_height;
			tex_pos += tex_step;

			color = arr[(tex_y * tex_line_size + tex_x)];
			(void)shading;
			// color = cb_darken_color(color, 3.5);
			cb_put_pixel(&ctx->img, rt->vec, color, 1.0f);
			rt->vec.y++;
		}
		while (rt->vec.y < SCREEN_HEIGHT && rt->vec.y > rd->draw_end)
		{
				cb_put_pixel(&ctx->img, rt->vec, FLOOR_COLOR, 1.0f);
				rt->vec.y++;
		}
		rt->vec.x++;
	}
	mlx_put_image_to_window(ctx->mlx, ctx->window, ctx->img.img, 0, 0);

	ctx->fps.new_time = get_time();
	ctx->fps.delta_time = ctx->fps.new_time - ctx->fps.old_time;
	ctx->fps.frame_count++;
	if (ctx->fps.delta_time >= 1000)
	{
		ctx->fps.fps = ctx->fps.frame_count * 1000 / ctx->fps.delta_time;
		ctx->fps.frame_count = 0;
		ctx->fps.old_time = get_time();
		ft_itoa_s(ctx->fps.time_str, (int)ctx->fps.fps);
	}
	mlx_string_put(ctx->mlx, ctx->window, 20, 30, 0xfff, ctx->fps.time_str);
	return (0);
}
