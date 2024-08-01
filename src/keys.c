/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okoca <okoca@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 11:33:47 by okoca             #+#    #+#             */
/*   Updated: 2024/08/01 20:02:54 by okoca            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

inline void	cb_move_updown(int keycode, t_map map, t_player *p)
{
	if (keycode == XK_W || keycode == XK_w)
	{
		if (map.raw[(map.width * (int)p->pos.y)
				+ (int)(p->pos.x + p->dir.x * FORCE)] != '1')
			p->pos.x += p->dir.x * FORCE;
		if (map.raw[(map.width * (int)(p->pos.y + p->dir.y * FORCE))
			+ (int)(p->pos.x)] != '1')
			p->pos.y += p->dir.y * FORCE;
	}
	if (keycode == XK_s || keycode == XK_S)
	{
		if (map.raw[(map.width * (int)p->pos.y)
				+ (int)(p->pos.x - p->dir.x * 0.1f)] != '1')
			p->pos.x -= p->dir.x * 0.1f;
		if (map.raw[(map.width
					* (int)(p->pos.y - p->dir.y * 0.1f)) + (int)(p->pos.x)] != '1')
			p->pos.y -= p->dir.y * 0.1f;
	}
}

inline void	cb_move_side(int keycode, t_map map, t_player *p)
{
	if (keycode == XK_d || keycode == XK_D)
	{
		if (map.raw[(map.width * (int)p->pos.y)
				+ (int)(p->pos.x + p->dir.y * 0.1f)] != '1')
			p->pos.x += p->dir.y * 0.1f;
		if (map.raw[(map.width
					* (int)(p->pos.y - p->dir.x * 0.1f))
					+ (int)(p->pos.x)] != '1')
			p->pos.y -= p->dir.x * 0.1f;
	}
	if (keycode == XK_a || keycode == XK_A)
	{
		if (map.raw[(map.width * (int)p->pos.y)
				+ (int)(p->pos.x - p->dir.y * 0.1f)] != '1')
			p->pos.x -= p->dir.y * 0.1f;
		if (map.raw[(map.width
					* (int)(p->pos.y + p->dir.x * 0.1f))
					+ (int)(p->pos.x)] != '1')
			p->pos.y += p->dir.x * 0.1f;
	}
}

inline void	cb_rotate(int keycode, t_player *p)
{
	float	old_dir_x;
	float	old_plane_x;

	old_dir_x = p->dir.x;
	old_plane_x = p->plane.x;
	if (keycode == XK_Right)
	{
		p->dir.x = p->dir.x * cos(-FORCE) - p->dir.y * sin(-FORCE);
		p->dir.y = old_dir_x * sin(-FORCE) + p->dir.y * cos(-FORCE);
		p->plane.x = p->plane.x * cos(-FORCE) - p->plane.y * sin(-FORCE);
		p->plane.y = old_plane_x * sin(-FORCE) + p->plane.y * cos(-FORCE);
	}
	if (keycode == XK_Left)
	{
		p->dir.x = p->dir.x * cos(FORCE) - p->dir.y * sin(FORCE);
		p->dir.y = old_dir_x * sin(FORCE) + p->dir.y * cos(FORCE);
		p->plane.x = p->plane.x * cos(FORCE) - p->plane.y * sin(FORCE);
		p->plane.y = old_plane_x * sin(FORCE) + p->plane.y * cos(FORCE);
	}
}

int	cb_handle_key(int keycode, void *data)
{
	t_ctx		*ctx;
	t_player	*player;

	ctx = (t_ctx *)data;
	player = &ctx->map.player;
	if (keycode == XK_Escape)
		cb_exit(ctx);
	cb_move_updown(keycode, ctx->map, player);
	cb_move_side(keycode, ctx->map, player);
	cb_rotate(keycode, player);
	return (0);
}

// more fluid keybinds