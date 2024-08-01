/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okoca <okoca@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 11:33:47 by okoca             #+#    #+#             */
/*   Updated: 2024/08/01 20:29:04 by okoca            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

inline void	cb_move_updown(t_ctx *ctx, t_map map, t_player *p)
{
	if (ctx->keys.up)
	{
		if (map.raw[(map.width * (int)p->pos.y)
				+ (int)(p->pos.x + p->dir.x * FORCE)] != '1')
			p->pos.x += p->dir.x * FORCE;
		if (map.raw[(map.width * (int)(p->pos.y + p->dir.y * FORCE))
			+ (int)(p->pos.x)] != '1')
			p->pos.y += p->dir.y * FORCE;
	}
	if (ctx->keys.down)
	{
		if (map.raw[(map.width * (int)p->pos.y)
				+ (int)(p->pos.x - p->dir.x * 0.1f)] != '1')
			p->pos.x -= p->dir.x * 0.1f;
		if (map.raw[(map.width
					* (int)(p->pos.y - p->dir.y * 0.1f)) + (int)(p->pos.x)] != '1')
			p->pos.y -= p->dir.y * 0.1f;
	}
}

inline void	cb_move_side(t_ctx *ctx, t_map map, t_player *p)
{
	if (ctx->keys.right)
	{
		if (map.raw[(map.width * (int)p->pos.y)
				+ (int)(p->pos.x + p->dir.y * 0.1f)] != '1')
			p->pos.x += p->dir.y * 0.1f;
		if (map.raw[(map.width
					* (int)(p->pos.y - p->dir.x * 0.1f))
					+ (int)(p->pos.x)] != '1')
			p->pos.y -= p->dir.x * 0.1f;
	}
	if (ctx->keys.left)
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

int	cb_key_up(int keycode, void *data)
{
	t_ctx	*ctx;
	t_keys	*keys;

	ctx = (t_ctx *)data;
	keys = &ctx->keys;
	if (keycode == XK_w || keycode == XK_W)
		keys->up = 0;
	if (keycode == XK_s || keycode == XK_S)
		keys->down = 0;
	if (keycode == XK_d || keycode == XK_D)
		keys->right = 0;
	if (keycode == XK_a || keycode == XK_A)
		keys->left = 0;
	return (0);
}

int	cb_key_down(int keycode, void *data)
{
	t_ctx	*ctx;
	t_keys	*keys;

	ctx = (t_ctx *)data;
	keys = &ctx->keys;
	if (keycode == XK_Escape)
		cb_exit(ctx);
	if (keycode == XK_w || keycode == XK_W)
		keys->up = 1;
	if (keycode == XK_s || keycode == XK_S)
		keys->down = 1;
	if (keycode == XK_d || keycode == XK_D)
		keys->right = 1;
	if (keycode == XK_a || keycode == XK_A)
		keys->left = 1;
	cb_rotate(keycode, &ctx->map.player);
	return (0);
}

int	cb_handle_key(t_ctx *ctx)
{
	t_player	*player;

	player = &ctx->map.player;
	cb_move_updown(ctx, ctx->map, player);
	cb_move_side(ctx, ctx->map, player);
	return (0);
}

// more fluid keybinds