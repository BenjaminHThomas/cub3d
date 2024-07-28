/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okoca <okoca@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/27 15:00:44 by okoca             #+#    #+#             */
/*   Updated: 2024/07/28 09:37:36 by okoca            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <fcntl.h>
# include <unistd.h>
# include <math.h>
# include <stdlib.h>
# include <X11/keysym.h>
# include <X11/X.h>

# include "mlx.h"
# include "libft.h"

# ifndef M_PI
#  define M_PI 3.14159265358979323846
# endif

typedef int	t_color;

typedef struct s_vec
{
	int	x;
	int	y;
}	t_vec;

typedef struct s_img
{
	int		bits_per_pixel;
	int		line_size;
	int		endian;
	char	*buffer;
	void	*img;
}	t_img;


typedef struct s_map
{
	char	**raw;
	t_vec	player;
}	t_map;

typedef struct s_ctx
{
	void	*mlx;
	void	*window;
	t_map	*map;
	float	fov;
}	t_ctx;

t_map	*init_map();

#endif
