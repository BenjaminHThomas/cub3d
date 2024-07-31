/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okoca <okoca@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 11:33:47 by okoca             #+#    #+#             */
/*   Updated: 2024/07/31 11:27:56 by okoca            ###   ########.fr       */
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
		player->dx = player->dx * cos(-0.1f) - player->dy * sin(-0.1f);
		player->dy = old_dir_x * sin(-0.1f) + player->dy * cos(-0.1f);

		float	old_plane_x = player->plane_x;
		player->plane_x = player->plane_x * cos(-0.1f) - player->plane_y * sin(-0.1f);
		player->plane_y = old_plane_x * sin(-0.1f) + player->plane_y * cos(-0.1f);
	}
	if (keycode == XK_Left)
	{
		float	old_dir_x = player->dx;
		player->dx = player->dx * cos(0.1f) - player->dy * sin(0.1f);
		player->dy = old_dir_x * sin(0.1f) + player->dy * cos(0.1f);

		float	old_plane_x = player->plane_x;
		player->plane_x = player->plane_x * cos(0.1f) - player->plane_y * sin(0.1f);
		player->plane_y = old_plane_x * sin(0.1f) + player->plane_y * cos(0.1f);
	}
	if (keycode == XK_w || keycode == XK_W)
	{
		if (ctx->map->raw[(ctx->map->width * (int)player->y) + (int)(player->x + player->dx * 0.1f)] != '1')
			player->x += player->dx * 0.1f;
		if (ctx->map->raw[(ctx->map->width * (int)(player->y + player->dy * 0.1f)) + (int)(player->x)] != '1')
			player->y += player->dy * 0.1f;
	}
	if (keycode == XK_s || keycode == XK_S)
	{
		if (ctx->map->raw[(ctx->map->width * (int)player->y) + (int)(player->x - player->dx * 0.1f)] != '1')
			player->x -= player->dx * 0.1f;
		if (ctx->map->raw[(ctx->map->width * (int)(player->y - player->dy * 0.1f)) + (int)(player->x)] != '1')
			player->y -= player->dy * 0.1f;
	}
	if (keycode == XK_d || keycode == XK_D)
	{
		if (ctx->map->raw[(ctx->map->width * (int)player->y) + (int)(player->x + player->dy * 0.1f)] != '1')
			player->x += player->dy * 0.1f;
		if (ctx->map->raw[(ctx->map->width * (int)(player->y - player->dx * 0.1f)) + (int)(player->x)] != '1')
			player->y -= player->dx * 0.1f;
	}
	if (keycode == XK_a || keycode == XK_A)
	{
		if (ctx->map->raw[(ctx->map->width * (int)player->y) + (int)(player->x - player->dy * 0.1f)] != '1')
			player->x -= player->dy * 0.1f;
		if (ctx->map->raw[(ctx->map->width * (int)(player->y + player->dx * 0.1f)) + (int)(player->x)] != '1')
			player->y += player->dx * 0.1f;
	}
	return (0);
}
