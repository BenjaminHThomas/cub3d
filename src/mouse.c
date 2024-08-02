/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okoca <okoca@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 13:28:20 by okoca             #+#    #+#             */
/*   Updated: 2024/08/02 14:11:52 by okoca            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	cb_mouse_move(int keycode, int x, int y, void *param)
{
	t_ctx	*ctx;

	ctx = (t_ctx *)param;
	(void)x;
	(void)y;
	if (keycode == 1)
		ctx->keys.mouse ^= 1;
	return (0);
}

void	cb_rot_right(t_player *p, float force)
{
	float	old_dir_x;
	float	old_plane_x;

	old_dir_x = p->dir.x;
	old_plane_x = p->plane.x;
	p->dir.x = p->dir.x * cos(-force) - p->dir.y * sin(-force);
	p->dir.y = old_dir_x * sin(-force) + p->dir.y * cos(-force);
	p->plane.x = p->plane.x * cos(-force) - p->plane.y * sin(-force);
	p->plane.y = old_plane_x * sin(-force) + p->plane.y * cos(-force);
}

void	cb_rot_left(t_player *p, float force)
{
	float	old_dir_x;
	float	old_plane_x;

	old_dir_x = p->dir.x;
	old_plane_x = p->plane.x;
	p->dir.x = p->dir.x * cos(force) - p->dir.y * sin(force);
	p->dir.y = old_dir_x * sin(force) + p->dir.y * cos(force);
	p->plane.x = p->plane.x * cos(force) - p->plane.y * sin(force);
	p->plane.y = old_plane_x * sin(force) + p->plane.y * cos(force);
}