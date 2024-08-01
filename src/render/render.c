/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okoca <okoca@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 15:30:20 by okoca             #+#    #+#             */
/*   Updated: 2024/08/01 12:13:14 by okoca            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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

inline void	cb_tex_data(t_ctx *ctx)
{
	t_tex		*tex;
	t_renderer	rd;
	t_raytracer	rt;
	t_texture	tex_data;

	tex = &ctx->renderer.tex;
	rd = ctx->renderer;
	rt = ctx->raytracer;
	tex_data = ctx->textures[rt.orientation];
	tex->width = tex_data.w;
	tex->height = tex_data.h;
	tex->pos.x = (int)(rd.wall_x * (double)tex->width);
	if ((rt.side == 0 && rt.ray_dir.x > 0)
		|| (rt.side == 1 && rt.ray_dir.y < 0))
		tex->pos.x = tex->width - tex->pos.x - 1;
	tex->step = (double)tex->height / rd.line_height;
	tex->tex_pos = (rd.draw_start - SCREEN_HEIGHT
			/ 2 + rd.line_height / 2) * tex->step;
	tex->data = (int *)tex_data.img.buffer;
	tex->line_size = tex_data.img.line_size / 4;
}

int	cb_mini_draw(void *data)
{
	int			color;
	t_ctx		*ctx;
	t_raytracer	*rt;
	t_renderer	*rd;
	t_tex		*tex;

	ctx = (t_ctx *)data;
	rt = &ctx->raytracer;
	rd = &ctx->renderer;
	tex = &ctx->renderer.tex;
	rt->vec.x = 0;
	rt->vec.y = 0;
	while (rt->vec.x < SCREEN_WIDTH)
	{
		cb_rt_set(ctx);
		cb_side_step(ctx);
		cb_check_hit(ctx);
		cb_wall_dist(ctx);
		cb_draw_data(ctx);
		cb_tex_data(ctx);
		rt->vec.y = 0;
		while (rt->vec.y < SCREEN_HEIGHT && rt->vec.y < rd->draw_start)
		{
			cb_put_pixel(&ctx->img, rt->vec, CEILLING_COLOR, 1.0f);
			rt->vec.y++;
		}
		while (rt->vec.y < SCREEN_HEIGHT && rt->vec.y
			>= rd->draw_start && rt->vec.y <= rd->draw_end)
		{
			tex->pos.y = (int)tex->tex_pos % tex->height;
			tex->tex_pos += tex->step;

			color = tex->data[(tex->pos.y * tex->line_size + tex->pos.x)];
			color = cb_darken_color(color, 3.5);
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
