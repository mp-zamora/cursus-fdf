/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpenas-z <mpenas-z@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 14:31:22 by mpenas-z          #+#    #+#             */
/*   Updated: 2024/10/03 12:19:11 by mpenas-z         ###   ########.fr       */
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
# include <fcntl.h>
# include <limits.h>
# include <math.h>

typedef struct s_fdf_map
{
	int	**map;
	int	size_x;
	int	size_y;
	int	**isometric;
	int	total_size;
	int	*max_coords;
	int	*gradient;
}	t_fdf_map;

/* PARSE */
int			get_max_x(int fd);
int			get_max_y(int fd);
void		free_buffers(char **buffers, int size);
t_fdf_map	*init_map(char *file);
int			**parse_map(int fd, int size_x, int size_y);
/* GRAPHICS */
void		ft_hook(void *param);
void		draw_map(t_fdf_map *map, mlx_image_t *img);
/* UTILS */
int			*fill_gradient(void);
int			**convert_to_iso(int **map, int size_x, int size_y);
int			**correct_offset(int **isometric, int total_size);
int			*get_max_coords(int **isometric, int total_size);
/* MAIN */
void		handle_error(char *message);
void		print_map(int **map, int size_y, int size_x);
void		free_fdf_map(t_fdf_map *map);
int			open_file(char *file);

#endif
