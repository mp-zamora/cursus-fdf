/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpenas-z <mpenas-z@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 14:31:22 by mpenas-z          #+#    #+#             */
/*   Updated: 2024/09/04 13:25:07 by mpenas-z         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H
# include "../libft/libft.h"
# include "get_next_line.h"
# include <stdlib.h>
# include <fcntl.h>
# include <limits.h>
# include <math.h>

/* PARSE */
int		get_max_x(int fd);
int		get_max_y(int fd);
int		**parse_map(int fd, int size_x, int size_y);
/* MAIN */
void	handle_error(void);
void	print_map(int **map, int size_y, int size_x);
int		open_file(char *file);

#endif
