/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpenas-z <mpenas-z@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 14:31:22 by mpenas-z          #+#    #+#             */
/*   Updated: 2024/10/19 12:14:11 by archangelus      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# define WIDTH 1280
# define HEIGHT 720

# include "../libft/libft.h"
# include "get_next_line.h"
# include <MLX42/MLX42.h>
# include <fcntl.h>
# include <limits.h>
# include <math.h>

typedef struct s_coords
{
	int		x;
	int		y;
	int		z;
	float	iso_x;
	float	iso_y;
}	t_coords;

typedef struct s_fdf_map
{
	int			size_x;
	int			size_y;
	int			total_size;
	int			max_z;
	int			min_z;
	int			current_palette;
	int			palette_amount;
	float		zoom;
	float		translation;
	float		rotation;
	mlx_t		*mlx;
	mlx_image_t	*img;
	t_coords	**map;
	uint32_t	**palette;
	float		*max_coords;
}	t_fdf_map;

/* PARSE */
t_fdf_map	*init_map(char *file);
t_coords	*process_row(char *buffer, int size_x, int y);
t_coords	**parse_map(int fd, int size_x, int size_y);
t_coords	assign_coords(int x, int y, int z, float alpha);
void		free_buffers(char **buffers, int size);
/* PARSE2 */
t_coords	**add_offset(t_coords **map, int size_x, int size_y);
float		*get_offset(t_coords **map, int size_x, int size_y);
t_coords	**add_scale(t_coords **map, int size_x, int size_y);
float		get_scale(t_coords **map, int size_x, int size_y);
/* GRAPHICS */
void		close_hook(void *param);
void		bonus_hook(mlx_key_data_t keydata, void *param);
void		paint_line(t_coords o, t_coords d, mlx_image_t *img, t_fdf_map *m);
void		draw_lines(t_fdf_map *map, mlx_image_t *img);
mlx_image_t	*render_map(t_fdf_map *map);
/* COLOR */
uint32_t	get_color(float coords[2], t_coords o, t_coords d, t_fdf_map *m);
int			get_r(int rgba);
int			get_g(int rgba);
int			get_b(int rgba);
uint32_t	**create_palette(void);
/* UTILS */
float		*get_max_coords(t_coords **map, int size_x, int size_y);
float		get_od_percent(float x, float y, t_coords o, t_coords d);
float		get_z_percent(int z, int max_z, int min_z);
float		get_percent(float coords[2], t_coords o, t_coords d, t_fdf_map *m);
/* UTILS 2 */
int			get_max_height(t_fdf_map *map);
int			get_min_height(t_fdf_map *map);
int			get_max_y(int fd);
int			get_max_x(int fd);
/* MAIN */
void		handle_error(char *message);
void		print_map(int **map, int size_y, int size_x);
void		free_fdf_map(t_fdf_map *map);
int			open_file(char *file);

#endif
