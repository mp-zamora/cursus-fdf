/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpenas-z <mpenas-z@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 14:31:22 by mpenas-z          #+#    #+#             */
/*   Updated: 2024/09/20 13:28:23 by mpenas-z         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H
# include "../libft/libft.h"
# include "get_next_line.h"
# include <MLX42/MLX42.h>
# include <stdlib.h>
# include <fcntl.h>
# include <limits.h>
# include <math.h>

# define WIDTH 512
# define HEIGHT 512

/* PARSE */
int		get_max_x(int fd);
int		get_max_y(int fd);
void	free_buffers(char **buffers, int size);
int		**parse_map(int fd, int size_x, int size_y);
/* GRAPHICS */
void	ft_hook(void *param);
/* MAIN */
void	handle_error(void);
void	print_map(int **map, int size_y, int size_x);
void	free_fdf_map(int **map, int size);
int		open_file(char *file);

#endif
