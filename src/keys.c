/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okoca <okoca@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 11:33:47 by okoca             #+#    #+#             */
/*   Updated: 2024/07/31 17:35:53 by okoca            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

inline void	cb_move_updown(int keycode, t_map map, t_player *p)
{
	if (keycode == XK_W || keycode == XK_w)
	{
		if (map.raw[(map.width * (int)p->y)
				+ (int)(p->x + p->dx * FORCE)] != '1')
			p->x += p->dx * FORCE;
		if (map.raw[(map.width * (int)(p->y + p->dy * FORCE))
			+ (int)(p->x)] != '1')
			p->y += p->dy * FORCE;
	}
	if (keycode == XK_s || keycode == XK_S)
	{
		if (map.raw[(map.width * (int)p->y)
				+ (int)(p->x - p->dx * 0.1f)] != '1')
			p->x -= p->dx * 0.1f;
		if (map.raw[(map.width
					* (int)(p->y - p->dy * 0.1f)) + (int)(p->x)] != '1')
			p->y -= p->dy * 0.1f;
	}
}

inline void	cb_move_side(int keycode, t_map map, t_player *p)
{
	if (keycode == XK_d || keycode == XK_D)
	{
		if (map.raw[(map.width * (int)p->y)
				+ (int)(p->x + p->dy * 0.1f)] != '1')
			p->x += p->dy * 0.1f;
		if (map.raw[(map.width
					* (int)(p->y - p->dx * 0.1f)) + (int)(p->x)] != '1')
			p->y -= p->dx * 0.1f;
	}
	if (keycode == XK_a || keycode == XK_A)
	{
		if (map.raw[(map.width * (int)p->y)
				+ (int)(p->x - p->dy * 0.1f)] != '1')
			p->x -= p->dy * 0.1f;
		if (map.raw[(map.width
					* (int)(p->y + p->dx * 0.1f)) + (int)(p->x)] != '1')
			p->y += p->dx * 0.1f;
	}
}

inline void	cb_rotate(int keycode, t_player *p)
{
	float	old_dir_x;
	float	old_plane_x;

	old_dir_x = p->dx;
	old_plane_x = p->plane_x;
	if (keycode == XK_Right)
	{
		p->dx = p->dx * cos(-FORCE) - p->dy * sin(-FORCE);
		p->dy = old_dir_x * sin(-FORCE) + p->dy * cos(-FORCE);
		p->plane_x = p->plane_x * cos(-FORCE) - p->plane_y * sin(-FORCE);
		p->plane_y = old_plane_x * sin(-FORCE) + p->plane_y * cos(-FORCE);
	}
	if (keycode == XK_Left)
	{
		p->dx = p->dx * cos(FORCE) - p->dy * sin(FORCE);
		p->dy = old_dir_x * sin(FORCE) + p->dy * cos(FORCE);
		p->plane_x = p->plane_x * cos(FORCE) - p->plane_y * sin(FORCE);
		p->plane_y = old_plane_x * sin(FORCE) + p->plane_y * cos(FORCE);
	}
}

int	cb_handle_key(int keycode, void *data)
{
	t_ctx	*ctx;
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