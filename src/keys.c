/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okoca <okoca@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 11:33:47 by okoca             #+#    #+#             */
/*   Updated: 2024/08/01 21:30:15 by okoca            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

inline void	cb_move_updown(t_ctx *ctx, t_map map, t_player *p, float force)
{
	if (ctx->keys.up)
	{
		if (map.raw[(map.width * (int)p->pos.y)
				+ (int)(p->pos.x + p->dir.x * force)] != '1')
			p->pos.x += p->dir.x * force;
		if (map.raw[(map.width * (int)(p->pos.y + p->dir.y * force))
			+ (int)(p->pos.x)] != '1')
			p->pos.y += p->dir.y * force;
	}
	if (ctx->keys.down)
	{
		if (map.raw[(map.width * (int)p->pos.y)
				+ (int)(p->pos.x - p->dir.x * force)] != '1')
			p->pos.x -= p->dir.x * force;
		if (map.raw[(map.width
					* (int)(p->pos.y - p->dir.y * force))
			+ (int)(p->pos.x)] != '1')
			p->pos.y -= p->dir.y * force;
	}
}

inline void	cb_move_side(t_ctx *ctx, t_map map, t_player *p, float force)
{
	if (ctx->keys.right)
	{
		if (map.raw[(map.width * (int)p->pos.y)
				+ (int)(p->pos.x + p->dir.y * force)] != '1')
			p->pos.x += p->dir.y * force;
		if (map.raw[(map.width
					* (int)(p->pos.y - p->dir.x * force))
			+ (int)(p->pos.x)] != '1')
			p->pos.y -= p->dir.x * force;
	}
	if (ctx->keys.left)
	{
		if (map.raw[(map.width * (int)p->pos.y)
				+ (int)(p->pos.x - p->dir.y * force)] != '1')
			p->pos.x -= p->dir.y * force;
		if (map.raw[(map.width
					* (int)(p->pos.y + p->dir.x * force))
			+ (int)(p->pos.x)] != '1')
			p->pos.y += p->dir.x * force;
	}
}

inline void	cb_rotate(t_ctx *ctx, t_player *p, float force)
{
	float	old_dir_x;
	float	old_plane_x;

	force *= 0.7f;
	old_dir_x = p->dir.x;
	old_plane_x = p->plane.x;
	if (ctx->keys.r_right)
	{
		p->dir.x = p->dir.x * cos(-force) - p->dir.y * sin(-force);
		p->dir.y = old_dir_x * sin(-force) + p->dir.y * cos(-force);
		p->plane.x = p->plane.x * cos(-force) - p->plane.y * sin(-force);
		p->plane.y = old_plane_x * sin(-force) + p->plane.y * cos(-force);
	}
	else if (ctx->keys.r_left)
	{
		p->dir.x = p->dir.x * cos(force) - p->dir.y * sin(force);
		p->dir.y = old_dir_x * sin(force) + p->dir.y * cos(force);
		p->plane.x = p->plane.x * cos(force) - p->plane.y * sin(force);
		p->plane.y = old_plane_x * sin(force) + p->plane.y * cos(force);
	}
}

int	cb_key_toggle(int keycode, void *data)
{
	t_ctx	*ctx;
	t_keys	*keys;

	ctx = (t_ctx *)data;
	keys = &ctx->keys;
	if (keycode == XK_Escape)
		cb_exit(ctx);
	if (keycode == XK_w || keycode == XK_W)
		keys->up ^= 1;
	if (keycode == XK_s || keycode == XK_S)
		keys->down ^= 1;
	if (keycode == XK_d || keycode == XK_D)
		keys->right ^= 1;
	if (keycode == XK_a || keycode == XK_A)
		keys->left ^= 1;
	if (keycode == XK_Left)
		keys->r_left ^= 1;
	if (keycode == XK_Right)
		keys->r_right ^= 1;
	return (0);
}

int	cb_handle_key(t_ctx *ctx)
{
	t_player	*player;
	t_keys		keys;
	float		force;

	player = &ctx->map.player;
	force = FORCE;
	keys = ctx->keys;
	if ((keys.up && keys.right) || (keys.up && keys.left))
		force /= 2.0f;
	else if ((keys.down && keys.right) || (keys.down && keys.left))
		force /= 2.0f;
	force *= ctx->fps.delta_time;
	cb_move_updown(ctx, ctx->map, player, force);
	cb_move_side(ctx, ctx->map, player, force);
	cb_rotate(ctx, &ctx->map.player, force);
	return (0);
}
