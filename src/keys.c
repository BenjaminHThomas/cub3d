/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okoca <okoca@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 11:33:47 by okoca             #+#    #+#             */
/*   Updated: 2024/07/29 17:27:57 by okoca            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	cb_handle_key(int keycode, void *data)
{
	t_ctx	*ctx;
	t_player	*player;

	ctx = (t_ctx *)data;
	player = &ctx->map->player;
	if (keycode == XK_Escape)
		cb_free_all(ctx);
	if (keycode == XK_Right)
	{
		float	old_dir_x = player->dx;
		player->dx = player->dx * cosf(-0.1f) - player->dy * sinf(-0.1f);
		player->dy = old_dir_x * sinf(-0.1f) + player->dy * cosf(-0.1f);

		float	old_plane_x = player->plane_x;
		player->plane_x = player->plane_x * cosf(-0.1f) - player->plane_y * sinf(-0.1f);
		player->plane_y = old_plane_x * sinf(-0.1f) + player->plane_y * cosf(-0.1f);
		cb_mini_draw(ctx);
	}
	if (keycode == XK_Left)
	{
		float	old_dir_x = player->dx;
		player->dx = player->dx * cosf(0.1f) - player->dy * sinf(0.1f);
		player->dy = old_dir_x * sinf(0.1f) + player->dy * cosf(0.1f);

		float	old_plane_x = player->plane_x;
		player->plane_x = player->plane_x * cosf(0.1f) - player->plane_y * sinf(0.1f);
		player->plane_y = old_plane_x * sinf(0.1f) + player->plane_y * cosf(0.1f);
		cb_mini_draw(ctx);
	}
	if (keycode == XK_w || keycode == XK_W)
	{
		player->x += player->dx * 0.1f;
		player->y += player->dy * 0.1f;
		cb_mini_draw(ctx);
	}
	if (keycode == XK_s || keycode == XK_S)
	{
		player->x -= player->dx * 0.1f;
		player->y -= player->dy * 0.1f;
		cb_mini_draw(ctx);
	}
	if (keycode == XK_d || keycode == XK_D)
	{
		ctx->map->player.x += cosf(ctx->map->player.angle) * 0.1f;
		ctx->map->player.y -= sinf(ctx->map->player.angle) * 0.1f;
		cb_mini_draw(ctx);
	}
	if (keycode == XK_a || keycode == XK_A)
	{
		ctx->map->player.x -= cosf(ctx->map->player.angle) * 0.1f;
		ctx->map->player.y += sinf(ctx->map->player.angle) * 0.1f;
		cb_mini_draw(ctx);
	}
	return (0);
}
