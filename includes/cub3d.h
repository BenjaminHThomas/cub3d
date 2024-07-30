/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okoca <okoca@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/27 15:00:44 by okoca             #+#    #+#             */
/*   Updated: 2024/07/30 11:17:53 by okoca            ###   ########.fr       */
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

# ifdef __GNUC__
#  define HOT __attribute__((hot))
#  define COLD __attribute__((cold))
# else
# define HOT
# define COLD
#endif

# define SCREEN_WIDTH 1280
# define SCREEN_HEIGHT 720

# define PRECISION 0.10f

# define FOV 4.0f

# ifndef M_PI
#  define M_PI 3.14159265358979323846
# endif

# define NORTH 0
# define SOUTH 1
# define WEST 2
# define EAST 3

typedef int	t_color;

typedef struct s_vec
{
	float	x;
	float	y;
	float	angle;
}	t_vec;

typedef struct s_player
{
	double	x;
	double	y;
	double	dx;
	double	dy;
	double	angle;
	double	plane_x;
	double	plane_y;
}	t_player;

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
	char	*raw;
	t_player	player;
	int		height;
	int		width;
}	t_map;

typedef struct s_texture
{
	void	*data;
	int		w;
	int		h;
	t_img	img;
}	t_texture;

typedef struct s_ctx
{
	void		*mlx;
	void		*window;
	t_map		*map;
	float		fov;
	t_img		*img;
	t_texture	*textures;
}	t_ctx;

t_map	*init_map();

int		cb_handle_key(int keycode, void *data);

int		cb_free_all(void *param) COLD;

void	cb_mini_draw(t_ctx *ctx) HOT;

void	cb_put_pixel(t_img *img, t_vec vec, t_color color, float shading) HOT;

int		init_textures(t_ctx *ctx) COLD;

int		parsing(char *path, t_ctx *ctx) COLD;

#endif
