// void	cb_mini_draw(t_ctx *ctx)
// {
// 	int		color;
// 	t_vec	vec;
// 	t_player	player;

// 	vec.x = 0;
// 	vec.y = 0;
// 	vec.angle = 0;
// 	color = 0x19987f;
// 	player = ctx->map->player;
// 	float f_depth = 12.0f;

// 	while (vec.x++ < SCREEN_WIDTH)
// 	{
// 		int	hit_wall = 0;
// 		float f_ray_angle = (player.angle - ctx->fov / 2.0f)
// 			+ ((float)vec.x / (float)SCREEN_WIDTH) * ctx->fov;
// 		float	f_distance_to_wall = 0.0f;
// 		float	f_eye_x = sinf(f_ray_angle);
// 		float	f_eye_y = cosf(f_ray_angle);
// 		float	f_sample_x = 0.0f;
// 		float	f_sample_y = 0.0f;
// 		float	wall_x = 0.0f;
// 		int		orientation;

// 		while (!hit_wall && f_distance_to_wall < f_depth)
// 		{
// 			f_distance_to_wall += PRECISION;

// 			int	n_test_x = (int)(player.x + f_eye_x * f_distance_to_wall);
// 			int	n_test_y = (int)(player.y + f_eye_y * f_distance_to_wall);
// 			if (n_test_x < 0 || n_test_x >= 12 || n_test_y < 0 || n_test_y >= 12)
// 			{
// 				hit_wall = 1;
// 				f_distance_to_wall = f_depth;
// 			}
// 			else
// 			{
// 				if (ctx->map->raw[n_test_y * ctx->map->width + n_test_x] == '1')
// 				{
// 					hit_wall = 1;

// 					// float f_block_mid_x = (float)n_test_x + 0.5f;
// 					// float f_block_mid_y = (float)n_test_y + 0.5f;

// 					float f_test_point_x = player.x + f_eye_x * f_distance_to_wall;
// 					float f_test_point_y = player.y + f_eye_y * f_distance_to_wall;

// 					// float f_test_angle = atan2f((f_test_point_y - f_block_mid_y), (f_test_point_x - f_block_mid_x));

// 					// if (n_test_x == (int)player.x + f_eye_x || n_test_x == (int)player.x - f_eye_x)
// 					// {
// 					// 	orientation = 1;
// 					// 	wall_x = player.y + f_eye_y * f_distance_to_wall;
// 					// }
// 					// else
// 					// {
// 					// 	orientation = 0;
// 					// 	wall_x = player.x + f_eye_x * f_distance_to_wall;
// 					// }
// 					// wall_x -= floorf(wall_x);

// 					// if (f_test_angle >= M_PI * 0.25f && f_test_angle < M_PI * 0.25f)
// 					// 	f_sample_x = f_test_point_y - (float)n_test_y;
// 					// if (f_test_angle >= M_PI * 0.25f && f_test_angle < M_PI * 0.75f)
// 					// 	f_sample_x = f_test_point_x - (float)n_test_x;
// 					// if (f_test_angle < M_PI * 0.25f && f_test_angle >= M_PI * 0.75f)
// 					// 	f_sample_x = f_test_point_x - (float)n_test_x;
// 					// if (f_test_angle >= M_PI * 0.75f || f_test_angle < M_PI * 0.75f)
// 					// 	f_sample_x = f_test_point_y - (float)n_test_y;

// 					float	block_edge_x = n_test_x + (f_eye_x > 0 ? 1 : 0);
// 					float	block_edge_y = n_test_y + (f_eye_y > 0 ? 1 : 0);
// 					(void)block_edge_y;

// 					float	dx = f_test_point_x - n_test_x;
// 					float	dy = f_test_point_y - n_test_y;

// 					if (fabsf(f_test_point_x - block_edge_x) < 0.01f)
// 					{
// 						orientation = f_eye_x > 0 ? 0 : 1;
// 						wall_x = dy;
// 					}
// 					else
// 					{
// 						orientation = f_eye_y > 0 ? 2 : 3;
// 						wall_x = dx;
// 					}

// 					// if (fabs(dx) > fabs(dy))
// 					// {
// 					// 	orientation = (f_eye_x > 0) ? 0 : 1;
// 					// 	wall_x = f_test_point_y - n_test_y;
// 					// }
// 					// else
// 					// {
// 					// 	orientation = (f_eye_y > 0) ? 2 : 3;
// 					// 	wall_x = f_test_point_x - n_test_x;
// 					// }
// 					// wall_x -= floorf(wall_x);


// 					// if (cosf(f_ray_angle) > 0.0001 || cosf(f_ray_angle) < -0.001)
// 					// {
// 					// 	wall_x = player.y + f_distance_to_wall * sinf(f_ray_angle);
// 					// }
// 					// else
// 					// {
// 					// 	wall_x = player.x + f_distance_to_wall + cosf(f_ray_angle);
// 					// }
// 					// wall_x -= floorf(wall_x);
// 				}
// 			}
// 		}

// 		int n_ceilling = (float)(SCREEN_HEIGHT / 2.0f) - SCREEN_HEIGHT / ((float)f_distance_to_wall);
// 		int n_floor = SCREEN_HEIGHT - n_ceilling;

// 		vec.y = 0;
// 		while (vec.y++ < SCREEN_HEIGHT)
// 		{
// 			if (vec.y < n_ceilling) // ceilling
// 			{
// 				color = 0x1affff;
// 				cb_put_pixel(ctx->img, vec, color, 1.0f);
// 			}
// 			else if (vec.y > n_ceilling && vec.y <= n_floor) // wall is here
// 			{
// 				f_sample_y = ((float)vec.y - (float)n_ceilling) / ((float)n_floor - (float)n_ceilling);

// 				// int *arr = (int*)ctx->textures.img.buffer;
// 				(void)f_sample_x;
// 				(void)f_sample_y;
// 				(void)wall_x;

// 				// if (orientation == 1 || orientation == 3)
// 				// 	wall_x = 1.0f - wall_x;

// 				// if (orientation == 1 && f_eye_x > 0)
// 				// 	wall_x = 1.0f - wall_x;
// 				// if (orientation == 0 && f_eye_y < 0)
// 				// 	wall_x = 1.0f - wall_x;

// 				// int	tex_x = (int)(wall_x * ctx->textures.w) % ctx->textures.w;
// 				// int	tex_x = (int)(f_sample_x * ctx->textures.w) % ctx->textures.w;
// 				// int	tex_y = (int)(f_sample_y * ctx->textures.h) % ctx->textures.h;
// 				switch(orientation)
// 				{
// 					case 0: color = 0xFF0000; break; // Red for west-facing walls
// 					case 1: color = 0x00FF00; break; // Green for east-facing walls
// 					case 2: color = 0x0000FF; break; // Blue for north-facing walls
// 					case 3: color = 0xFFFF00; break; // Yellow for south-facing walls
// 					default: color = 0xFFFFFF; break; // White for unknown orientation
// 				}
// 				float shading = 1.0f - (f_distance_to_wall / f_depth);
// 				// int color = arr[(tex_y * (ctx->textures.img.line_size / 4) + tex_x)];

// 				cb_put_pixel(ctx->img, vec, color, shading);
// 			}
// 			else // floor
// 			{
// 				color = 0x100fff;
// 				cb_put_pixel(ctx->img, vec, color, 1.0f);
// 			}
// 		}
// 	}
// 	mlx_put_image_to_window(ctx->mlx, ctx->window, ctx->img->img, 0, 0);
// }