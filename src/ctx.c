/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ctx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okoca <okoca@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 11:32:40 by okoca             #+#    #+#             */
/*   Updated: 2024/07/31 11:46:04 by okoca            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_ctx	cb_init_ctx()
{
	t_ctx	ctx;

	ctx.img = NULL;
	ctx.window = NULL;
	ctx.mlx = NULL;
	ctx.map = NULL;
	ft_bzero(ctx.fps.time_str, 2);
	ctx.fps.delta_time = 0;
	ctx.fps.frame_count = 0;
	ctx.fps.fps = 0;
	ctx.fps.old_time = get_time();
	return (ctx);
}
