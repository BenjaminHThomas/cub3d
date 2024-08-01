/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pixel.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okoca <okoca@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 11:50:06 by okoca             #+#    #+#             */
/*   Updated: 2024/08/01 13:45:53 by okoca            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

inline int	cb_clamp(int color)
{
	if (color > 255)
		return (255);
	return (color);
}

inline int	cb_noise(void)
{
	uint64_t	rnd;
	int			inc;

	inc = 90;
	rnd = get_time() / 30;
	return (rnd % inc - inc / 2);
}

inline int	cb_darken_color(int color, float shade)
{
	int	red;
	int	green;
	int	blue;
	int	noise;

	red = cb_clamp(((color >> 16) & 0xFF) * shade);
	green = cb_clamp(((color >> 8) & 0xFF) * shade);
	blue = cb_clamp((color & 0xFF) * shade);
	noise = cb_noise();
	red += noise;
	green += noise;
	blue += noise;
	if (red > 128)
		red = cb_min(255, red + 50);
	else
		red = cb_max(0, red - 50);
	if (green > 128)
		green = cb_min(255, green + 50);
	else
		green = cb_max(0, green - 50);
	if (blue > 128)
		blue = cb_min(255, blue + 50);
	else
		blue = cb_max(0, blue - 50);
	return ((red << 16) | (green << 8) | blue);
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
