/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okoca <okoca@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/27 13:57:19 by okoca             #+#    #+#             */
/*   Updated: 2024/08/02 14:12:08 by okoca            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

inline unsigned long	get_time(void)
{
	struct timeval	time;
	unsigned long	ms;

	gettimeofday(&time, NULL);
	ms = (time.tv_sec * (unsigned long)1000) + (time.tv_usec / 1000);
	return (ms);
}

int	cb_exit(void *param)
{
	t_ctx	*ctx;

	ctx = (t_ctx *)param;
	cb_free_all(ctx);
	exit(0);
}

int	main(int ac, char **av)
{
	t_ctx	ctx;

	(void)ac;
	(void)av;
	ctx = cb_init_ctx();
	if (cb_init_mtx(&ctx) != 0)
		return (1);
	cb_loop(&ctx);
	cb_free_all(&ctx);
}

int	cb_loop(t_ctx *ctx)
{
	if (USE_CUSTOM_FONT)
		mlx_set_font(ctx->mlx, ctx->window, "-*-*-*-*-*-*-20-*-*-*-*-*-*-*");
	mlx_hook(ctx->window, DestroyNotify, StructureNotifyMask, cb_exit, ctx);
	mlx_hook(ctx->window, KeyPress, KeyPressMask, cb_key_toggle, ctx);
	mlx_hook(ctx->window, KeyRelease, KeyReleaseMask, cb_key_toggle, ctx);
	mlx_hook(ctx->window, ButtonPress, ButtonPressMask, cb_mouse_move, ctx);
	mlx_hook(ctx->window, ButtonRelease, ButtonReleaseMask, cb_mouse_move, ctx);
	mlx_loop_hook(ctx->mlx, cb_mini_draw, ctx);
	mlx_loop(ctx->mlx);
	return (0);
}
