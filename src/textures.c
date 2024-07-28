/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okoca <okoca@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 16:16:50 by okoca             #+#    #+#             */
/*   Updated: 2024/07/28 16:22:23 by okoca            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	init_textures(t_ctx *ctx)
{
	ctx->textures.data = mlx_xpm_file_to_image(ctx->mlx, "textures/ground.xpm",
			&ctx->textures.w, &ctx->textures.h);
	if (!ctx->textures.data)
		return (1);
	return (0);
}
