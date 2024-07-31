/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okoca <okoca@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/27 15:00:44 by okoca             #+#    #+#             */
/*   Updated: 2024/07/31 10:05:55 by okoca            ###   ########.fr       */
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

# define CEILLING_COLOR 0x70129a
# define FLOOR_COLOR 0x0fa0b9

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

typedef struct s_raytracer
{
	t_vec	vec;
	double	camera_x;
	double	ray_dir_x;
	double	ray_dir_y;
	int		map_x;
	int		map_y;
	double	side_dist_x;
	double	side_dist_y;
	double	delta_dist_x;
	double	delta_dist_y;
	int		step_x;
	int		step_y;
	int		hit;
	int		side;
	int		orientation;
	double	distance_to_wall;
}	t_raytracer;

typedef	struct s_renderer
{
	int		line_height;
	int		draw_start;
	int		draw_end;
	double	wall_x;
	int		tex_width;
	int		tex_height;
	int		tex_x;
	int		tex_y;
	double	step;
	double	text_pos;
}	t_renderer;

typedef struct s_ctx
{
	void		*mlx;
	void		*window;
	t_map		*map;
	float		fov;
	t_img		*img;
	t_texture	*textures;
	t_renderer	renderer;
	t_raytracer	raytracer;
}	t_ctx;

t_map	*init_map();

int		cb_handle_key(int keycode, void *data);

int		cb_free_all(void *param) COLD;

// void	cb_mini_draw(t_ctx *ctx) HOT;
int		cb_mini_draw(void *data) HOT;

void	cb_put_pixel(t_img *img, t_vec vec, t_color color, float shading) HOT;

int		cb_darken_color(int color, float shade) HOT;

int		init_textures(t_ctx *ctx) COLD;

int		parsing(char *path, t_ctx *ctx) COLD;

#endif
