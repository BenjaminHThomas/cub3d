/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okoca <okoca@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 15:30:20 by okoca             #+#    #+#             */
/*   Updated: 2024/08/01 13:58:41 by okoca            ###   ########.fr       */
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

inline void	cb_draw_ceilling_floor(t_ctx *ctx, int flag)
{
	t_raytracer	*rt;
	t_renderer	*rd;

	rt = &ctx->raytracer;
	rd = &ctx->renderer;
	if (flag == 0)
	{
		while (rt->vec.y < SCREEN_HEIGHT && rt->vec.y < rd->draw_start)
		{
			cb_put_pixel(&ctx->img, rt->vec, CEILLING_COLOR, 1.0f);
			rt->vec.y++;
		}
		return ;
	}
	while (rt->vec.y < SCREEN_HEIGHT && rt->vec.y > rd->draw_end)
	{
		cb_put_pixel(&ctx->img, rt->vec, FLOOR_COLOR, 1.0f);
		rt->vec.y++;
	}
}

// color = cb_darken_color(color, 1.0f);
inline void	cb_draw_wall(t_ctx *ctx)
{
	t_raytracer	*rt;
	t_renderer	*rd;
	t_tex		*tex;
	t_color		color;

	tex = &ctx->renderer.tex;
	rt = &ctx->raytracer;
	rd = &ctx->renderer;
	while (rt->vec.y < SCREEN_HEIGHT && rt->vec.y
		>= rd->draw_start && rt->vec.y <= rd->draw_end)
	{
		tex->pos.y = (int)tex->tex_pos % tex->height;
		tex->tex_pos += tex->step;
		color = tex->data[(tex->pos.y * tex->line_size + tex->pos.x)];
		cb_put_pixel(&ctx->img, rt->vec, color, 1.0f);
		rt->vec.y++;
	}
}

int	cb_mini_draw(void *data)
{
	t_ctx		*ctx;
	t_raytracer	*rt;

	ctx = (t_ctx *)data;
	rt = &ctx->raytracer;
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
		cb_draw_ceilling_floor(ctx, 0);
		cb_draw_wall(ctx);
		cb_draw_ceilling_floor(ctx, 1);
		rt->vec.x++;
	}
	mlx_put_image_to_window(ctx->mlx, ctx->window, ctx->img.img, 0, 0);
	cb_draw_fps(ctx);
	return (0);
}
