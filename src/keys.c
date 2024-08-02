/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okoca <okoca@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 11:33:47 by okoca             #+#    #+#             */
/*   Updated: 2024/08/02 14:15:36 by okoca            ###   ########.fr       */
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

void	cb_rotate(t_ctx *ctx, t_player *p, float force)
{
	float	old_dir_x;
	float	old_plane_x;
	t_keys	keys;

	force *= 0.7f;
	old_dir_x = p->dir.x;
	old_plane_x = p->plane.x;
	keys = ctx->keys;
	if (keys.r_right || (keys.mouse && keys.m_pos.x > SCREEN_WIDTH / 2))
		cb_rot_right(p, force);
	if (keys.r_left || (keys.mouse && keys.m_pos.x <= SCREEN_WIDTH / 2))
		cb_rot_left(p, force);
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

	mlx_mouse_get_pos(ctx->mlx, ctx->window,
		&ctx->keys.m_pos.x, &ctx->keys.m_pos.y);
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
	cb_rotate(ctx, &ctx->map.player, FORCE * ctx->fps.delta_time);
	return (0);
}
