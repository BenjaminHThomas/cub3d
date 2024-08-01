/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pixel.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okoca <okoca@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 11:50:06 by okoca             #+#    #+#             */
/*   Updated: 2024/08/01 11:51:39 by okoca            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

inline int	cb_clamp(int color)
{
	if (color > 255)
		return (255);
	return (color);
}

inline int	cb_darken_color(int color, float shade)
{
	int	new;
	int	red;
	int	green;
	int	blue;

	red = cb_clamp(((color >> 16) & 0xFF) * shade);
	green = cb_clamp(((color >> 8) & 0xFF) * shade);
	blue = cb_clamp((color & 0xFF) * shade);
	new = (red << 16) | (green << 8) | blue;
	return (new);
}

inline void	cb_put_pixel(t_img *img, t_vecint vec, t_color color, float shading)
{
	int	pixel;
	int	*buffer;

	pixel = (vec.y * (img->line_size / 4)) + (vec.x);
	buffer = (int *)img->buffer;
	color *= shading;
	if (buffer[pixel] != color)
		buffer[pixel] = color;
}
