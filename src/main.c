/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okoca <okoca@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/27 13:57:19 by okoca             #+#    #+#             */
/*   Updated: 2024/07/31 11:46:22 by okoca            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

inline unsigned long	get_time()
{
	struct timeval	time;
	unsigned long ms;

	gettimeofday(&time, NULL);
	ms = (time.tv_sec * (unsigned long)1000) + (time.tv_usec / 1000);
	return (ms);
}

int	cb_free_all(void *param)
{
	t_ctx	*ctx;
	int		i;

	i = 0;
	ctx = (t_ctx *)param;
	if (ctx->map && ctx->map->raw)
	{
		free(ctx->map->raw);
		free(ctx->map);
	}
	if (ctx->mlx)
	{
		if (ctx->textures)
		{
			while (i < 4)
			{
				mlx_destroy_image(ctx->mlx, ctx->textures[i].data);
				i++;
			}
			free(ctx->textures);
		}
		if (ctx->img)
		{
			mlx_destroy_image(ctx->mlx, ctx->img->img);
			free(ctx->img);
		}
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
	exit(0);
}


int	main(int ac, char **av)
{
	t_ctx	ctx;
	int		i;

	i = 0;
	(void)ac;
	(void)av;
	// if (check_args(av, av) != 0)
	// 	return (1);
	// if (parsing(av[1], &ctx) != 0)
	// 	return (1);
	ctx = cb_init_ctx();
	ctx.map = init_map();
	while (i < ctx.map->height)
	{
		printf("%.12s\n", &(ctx.map->raw[i * ctx.map->width]));
		i++;
	}
	ctx.mlx = mlx_init();
	if (init_textures(&ctx) != 0)
	{
		printf("entered this\n");
		free(ctx.map->raw);
		free(ctx.map);
		mlx_destroy_display(ctx.mlx);
		free(ctx.mlx);
		return (1);
	}
	ctx.img = malloc(sizeof(t_img));
	ctx.img->img = mlx_new_image(ctx.mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
	ctx.img->buffer = mlx_get_data_addr(ctx.img->img, &ctx.img->bits_per_pixel, &ctx.img->line_size, &ctx.img->endian);
	ctx.window = mlx_new_window(ctx.mlx, SCREEN_WIDTH, SCREEN_HEIGHT, "cub3d");
	mlx_hook(ctx.window, DestroyNotify, StructureNotifyMask, cb_free_all, &ctx);
	mlx_hook(ctx.window, KeyPress, KeyPressMask, cb_handle_key, &ctx);
	mlx_loop_hook(ctx.mlx, cb_mini_draw, &ctx);
	mlx_loop(ctx.mlx);
	cb_free_all(&ctx);
}

