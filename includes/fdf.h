/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpenas-z <mpenas-z@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 14:31:22 by mpenas-z          #+#    #+#             */
/*   Updated: 2024/11/09 17:47:57 by mpenas-z         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# ifndef WIDTH
#  define WIDTH 1280
# endif
# ifndef HEIGHT
#  define HEIGHT 720
# endif

# include "../libft/libft.h"
# include "../libft/get_next_line.h"
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
	int			projection;
	float		zoom;
	float		scale;
	float		theta;
	float		*center;
	float		*max_coords;
	char		*file;
	mlx_t		*mlx;
	mlx_image_t	*img;
	t_coords	**map;
	t_coords	**original;
	uint32_t	**palette;
}	t_fdf_map;

/* PARSE */
t_fdf_map	*init_map(char *file);
void		assign_data(t_fdf_map **fdf_map);
t_coords	*process_row(char *buffer, int size_x, int y);
t_coords	**parse_map(int fd, int size_x, int size_y);
t_coords	assign_coords(int x, int y, int z);
/* PARSE2 */
t_coords	**add_offset(t_coords **map, int size_x, int size_y);
float		*get_offset(t_coords **map, int size_x, int size_y);
t_coords	**add_scale(t_coords **map, int size_x, int size_y);
float		get_scale(t_coords **map, int size_x, int size_y);
t_coords	**apply_zoom(t_coords **map, int size_x, int size_y, float zoom);
/* GRAPHICS */
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
int			get_max_height(t_fdf_map *map);
int			get_min_height(t_fdf_map *map);
int			get_max_y(int fd);
int			get_max_x(int fd);
/* UTILS 2 */
float		get_od_percent(float x, float y, t_coords o, t_coords d);
float		get_z_percent(int z, int max_z, int min_z);
float		get_percent(float coords[2], t_coords o, t_coords d, t_fdf_map *m);
float		*get_min_coords(t_coords **map, int size_x, int size_y);
void		free_buffers(char **buffers, int size);
/* UTILS 3 */
void		center_map(t_fdf_map **map);
void		add_x_offset(t_fdf_map **map, float offset);
void		add_y_offset(t_fdf_map **map, float offset);
t_coords	**recalculate_map(t_fdf_map *map);
/* BONUS */
mlx_image_t	*add_zoom(float zoom, t_fdf_map **map);
mlx_image_t	*add_translation(float tx, float ty, t_fdf_map **map);
mlx_image_t	*add_rotation(float theta, t_fdf_map **map);
void		apply_projection_change(int projection, t_fdf_map **map);
mlx_image_t *perspective_projection(int projection, t_fdf_map **map);
/* HOOKS */
void		close_hook(void *param);
void		bonus_hook(mlx_key_data_t keydata, void *param);
void		handle_projection_key(mlx_key_data_t keydata, t_fdf_map **map);
void		handle_translation_key(mlx_key_data_t keydata, t_fdf_map **map);
void		handle_zoom_rotation_key(mlx_key_data_t keydata, t_fdf_map **map);
/* MAIN */
void		handle_error(char *message);
void		free_fdf_map(t_fdf_map *map);
void		free_fdf_map_arrays(t_fdf_map *map);
int			open_file(char *file);

#endif
