/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extra.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okoca <okoca@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 13:05:48 by okoca             #+#    #+#             */
/*   Updated: 2024/08/01 13:45:28 by okoca            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

inline void	cb_draw_fps(t_ctx *ctx)
{
	ctx->fps.new_time = get_time();
	ctx->fps.delta_time = ctx->fps.new_time - ctx->fps.old_time;
	ctx->fps.frame_count++;
	if (ctx->fps.delta_time >= 1000)
	{
		ctx->fps.fps = ctx->fps.frame_count * 1000 / ctx->fps.delta_time;
		ctx->fps.frame_count = 0;
		ctx->fps.old_time = get_time();
		ft_itoa_s(ctx->fps.time_str, (int)ctx->fps.fps);
	}
	mlx_string_put(ctx->mlx, ctx->window, 20, 30, 0xfff, ctx->fps.time_str);
}

inline int	cb_max(int a, int b)
{
	if (a > b)
		return (a);
	return (b);
}

inline int	cb_min(int a, int b)
{
	if (a < b)
		return (a);
	return (b);
}
