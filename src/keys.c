/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okoca <okoca@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 11:33:47 by okoca             #+#    #+#             */
/*   Updated: 2024/07/28 14:19:15 by okoca            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	cb_handle_key(int keycode, void *data)
{
	t_ctx	*ctx;

	ctx = (t_ctx *)data;
	if (keycode == XK_Escape)
		cb_free_all(ctx);
	else if (keycode == XK_Right)
	{
		ctx->map->player.angle += 0.2f;
		cb_mini_draw(ctx);
	}
	else if (keycode == XK_Left)
	{
		ctx->map->player.angle -= 0.2f;
		cb_mini_draw(ctx);
	}
	else if (keycode == XK_w || keycode == XK_W)
	{
		ctx->map->player.x += sinf(ctx->map->player.angle) * 0.1f;
		ctx->map->player.y += cosf(ctx->map->player.angle) * 0.1f;
		cb_mini_draw(ctx);
	}
	else if (keycode == XK_s || keycode == XK_S)
	{
		ctx->map->player.x -= sinf(ctx->map->player.angle) * 0.1f;
		ctx->map->player.y -= cosf(ctx->map->player.angle) * 0.1f;
		cb_mini_draw(ctx);
	}
	else if (keycode == XK_d || keycode == XK_D)
	{
		ctx->map->player.x += cosf(ctx->map->player.angle) * 0.1f;
		ctx->map->player.y -= sinf(ctx->map->player.angle) * 0.1f;
		cb_mini_draw(ctx);
	}
	else if (keycode == XK_a || keycode == XK_A)
	{
		ctx->map->player.x -= cosf(ctx->map->player.angle) * 0.1f;
		ctx->map->player.y += sinf(ctx->map->player.angle) * 0.1f;
		cb_mini_draw(ctx);
	}
	return (0);
}
