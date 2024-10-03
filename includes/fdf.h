/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpenas-z <mpenas-z@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 14:31:22 by mpenas-z          #+#    #+#             */
/*   Updated: 2024/10/03 20:02:38 by archangelus      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# define WIDTH 512
# define HEIGHT 512

# include "../libft/libft.h"
# include "get_next_line.h"
# include <MLX42/MLX42.h>
# include <stdlib.h>
// REMOVE
# include <stdio.h>
// REMOVE UP
# include <fcntl.h>
# include <limits.h>
# include <math.h>

// Struct idea:
// Both 3d coordinates and 2d coordinates of a point. Navigate trough the 3d
// coords, operate with the 2d coords.
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
	t_coords **map;
	int		size_x;
	int		size_y;
	/*float	**isometric;*/
	int		total_size;
	float	*max_coords;
	int		*gradient;
}	t_fdf_map;

/* PARSE */
int			get_max_x(int fd);
int			get_max_y(int fd);
void		free_buffers(char **buffers, int size);
t_fdf_map	*init_map(char *file);
t_coords	**parse_map(int fd, int size_x, int size_y);
float		*get_offset(t_coords **map, int size_x, int size_y);
t_coords	assign_coords(int x, int y, int z, float alpha, float scale);
t_coords	**add_offset(t_coords **map, int size_x, int size_y);
/* GRAPHICS */
void		ft_hook(void *param);
void		draw_map(t_fdf_map *map, mlx_image_t *img);
/* UTILS */
int			*fill_gradient(void);
/*float		**convert_to_iso(int **map, int size_x, int size_y, float alpha);*/
/*float		**correct_offset(float **isometric, int total_size);*/
float		*get_max_coords(t_coords **map, int size_x, int size_y);
/* MAIN */
void		handle_error(char *message);
void		print_map(int **map, int size_y, int size_x);
void		free_fdf_map(t_fdf_map *map);
int			open_file(char *file);

#endif
