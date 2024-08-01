/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okoca <okoca@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 11:54:17 by okoca             #+#    #+#             */
/*   Updated: 2024/08/01 12:09:47 by okoca            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDER_H
# define RENDER_H

typedef struct s_vec
{
	double	x;
	double	y;
}	t_vec;

typedef struct s_vecint
{
	int	x;
	int	y;
}	t_vecint;

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
	t_vecint	vec;
	double		camera_x;
	t_vec		ray_dir;
	t_vecint	map_check;
	t_vec		side_dist;
	t_vec		delta_dist;
	t_vecint	step;
	int			hit;
	int			side;
	int			orientation;
	double		distance_to_wall;
}	t_raytracer;

typedef struct s_tex
{
	int			width;
	int			height;
	t_vecint	pos;
	double		tex_pos;
	double		step;
	int			*data;
	int			line_size;
}	t_tex;

typedef struct s_renderer
{
	int			line_height;
	int			draw_start;
	int			draw_end;
	double		wall_x;
	t_tex		tex;
}	t_renderer;

typedef struct s_fps
{
	unsigned long		old_time;
	unsigned long		new_time;
	unsigned long		frame_count;
	unsigned long		delta_time;
	unsigned long		fps;
	char				time_str[21];
}	t_fps;

#endif