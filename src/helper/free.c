/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okoca <okoca@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 14:58:03 by okoca             #+#    #+#             */
/*   Updated: 2024/07/31 16:19:21 by okoca            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	cb_free_map(t_ctx *ctx)
{
	if (ctx->map.raw)
		free(ctx->map.raw);
}

void	cb_free_tex(t_ctx *ctx)
{
	int	i;

	i = 0;
	if (ctx->textures)
	{
		while (i < 4)
		{
			mlx_destroy_image(ctx->mlx, ctx->textures[i].data);
			i++;
		}
		free(ctx->textures);
	}
	if (ctx->img.img)
		mlx_destroy_image(ctx->mlx, ctx->img.img);
}

int	cb_free_all(t_ctx *ctx)
{
	cb_free_map(ctx);
	if (ctx->mlx)
	{
		cb_free_tex(ctx);
		mlx_loop_end(ctx->mlx);
		if (ctx->window)
		{
			mlx_destroy_window(ctx->mlx, ctx->window);
			ctx->window = NULL;
		}
		mlx_destroy_display(ctx->mlx);
		free(ctx->mlx);
		ctx->mlx = NULL;
	}
	return (0);
}
