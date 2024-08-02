/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extra.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okoca <okoca@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 13:05:48 by okoca             #+#    #+#             */
/*   Updated: 2024/08/02 12:12:08 by okoca            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

inline void	cb_draw_fps(t_ctx *ctx)
{
	t_fps			*fps;
	static float	elapsed;

	fps = &ctx->fps;
	gettimeofday(&fps->new_time, NULL);
	fps->delta_time = (fps->new_time.tv_sec - fps->old_time.tv_sec)
		+ (fps->new_time.tv_usec - fps->old_time.tv_usec) / 1000000.0f;
	fps->old_time = fps->new_time;
	fps->frame_count++;
	elapsed += fps->delta_time;
	if (elapsed >= fps->interval)
	{
		fps->fps = fps->frame_count / elapsed;
		ft_itoa_s(ctx->fps.time_str, (int)ctx->fps.fps);
		fps->frame_count = 0;
		elapsed = 0.0f;
	}
	mlx_string_put(ctx->mlx, ctx->window, 20, 30, 0xfff, ctx->fps.time_str);
}

inline void	cb_draw_square(t_ctx *ctx, t_vecint vec, t_color color, int area)
{
	int			x;
	int			y;
	t_vecint	tmp;
	int			def;
	int			minimap_side;

	x = 0;
	def = color;
	minimap_side = 2;
	while (x < area)
	{
		y = 0;
		while (y < area)
		{
			tmp.x = (vec.x * area) + x;
			tmp.y = (vec.y * area) + y;
			color = def;
			if (x < minimap_side || x > area - minimap_side)
				color = 0x000;
			if (y < minimap_side || y > area - minimap_side)
				color = 0x000;
			cb_put_pixel(&ctx->img, tmp, color, 1.0f);
			y++;
		}
		x++;
	}
}

inline void	cb_draw_player(t_ctx *ctx, t_vec player, t_color color, int area)
{
	int			x;
	int			y;
	t_vecint	tmp;

	x = 0;
	while (x < area)
	{
		y = 0;
		while (y < area)
		{
			tmp.x = (int)(player.x * (double)area) + x;
			tmp.y = (int)(player.y * (double)area) + y;
			cb_put_pixel(&ctx->img, tmp, color, 1.0f);
			y++;
		}
		x++;
	}
}

inline void	cb_draw_minimap(t_ctx *ctx)
{
	t_map		map;
	t_vecint	vec;

	vec.x = 0;
	map = ctx->map;
	while (vec.x < map.width)
	{
		vec.y = 0;
		while (vec.y < map.height)
		{
			if (map.raw[vec.y * map.width + vec.x] == '1')
				cb_draw_square(ctx, vec, MINIMAP_WALL, MINIMAP_SIZE);
			else if (map.raw[vec.y * map.width + vec.x] == '0')
				cb_draw_square(ctx, vec, MINIMAP_FLOOR, MINIMAP_SIZE);
			vec.y++;
		}
		vec.x++;
	}
	map.player.pos.x -= 0.5f;
	map.player.pos.y -= 0.5f;
	cb_draw_player(ctx, map.player.pos, MINIMAP_PLAYER, MINIMAP_SIZE);
}
