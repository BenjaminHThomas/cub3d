/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bthomas <bthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 11:08:25 by bthomas           #+#    #+#             */
/*   Updated: 2024/08/02 11:46:55 by bthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H

# include "cub3d.h"

typedef enum e_direction
{
	NORTH,
	SOUTH,
	WEST,
	EAST
}	t_direction;

typedef struct s_tex_path
{
	t_direction	dir;
	char		*path;
}	t_tex_path;

typedef struct s_map_data
{
	int				fd;
	char			**input;
	char			**map;
	t_tex_path		**tex_paths;
	unsigned int	f_colour;
	unsigned int	c_colour;
}	t_map_data;

t_tex_path		**get_textures(t_map_data *map_data);
void			get_file_contents(t_map_data *mapdata);
int				init_input(t_map_data *mapdata, char *fname);
int				get_hex_colour(t_map_data *mapdata, int idx);
int				read_map(t_map_data *mapdata);

/* Input Validation */
bool			valid_fname(char *fname);
bool			valid_textures(t_map_data *mapdata);
bool			valid_map(t_map_data *mapdata);

/* General Utilities */
int				resize_arr(char ***arr, int *size);
size_t			array_len(void	**arr);
unsigned int	rgb_to_hex(unsigned char r, unsigned char g, unsigned char b);
void			print_input(t_map_data *mapdata);
size_t			get_max_map_len(t_map_data *mapdata);
void			fill_map_void(t_map_data *mapdata);

/* Boolean helper functions*/
bool			is_empty_line(char *line);
bool			is_space(unsigned char c);
bool			in(unsigned char c, char *s);

/* Garbage collection */
void			free_arr(void **arr);
void			bin_textures(t_tex_path **texts);

#endif
