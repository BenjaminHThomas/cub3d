/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okoca <okoca@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 11:33:47 by okoca             #+#    #+#             */
/*   Updated: 2024/07/28 11:36:11 by okoca            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	cb_handle_key(int keycode, void *data)
{
	t_ctx	*ctx;

	ctx = (t_ctx *)data;
	if (keycode == XK_Escape)
		cb_free_all(ctx);
	return (0);
}
