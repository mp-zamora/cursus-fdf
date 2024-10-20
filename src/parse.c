/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpenas-z <mpenas-z@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 11:38:49 by mpenas-z          #+#    #+#             */
/*   Updated: 2024/10/20 13:52:00 by mpenas-z         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

t_fdf_map	*init_map(char *file)
{
	t_fdf_map	*map;

	map = (t_fdf_map *)malloc(sizeof(t_fdf_map));
	if (!map)
		handle_error("Malloc failed.");
	map->size_x = get_max_x(open_file(file));
	map->size_y = get_max_y(open_file(file));
	map->map = parse_map(open_file(file), map->size_x, map->size_y);
	if (!map)
		handle_error("Parsing failed.");
	map->total_size = map->size_x * map->size_y;
	map->max_coords = get_max_coords(map->map, map->size_x, map->size_y);
	map->max_z = get_max_height(map);
	map->min_z = get_min_height(map);
	map->file = file;
	map->zoom = 1;
	map->center = (float *)malloc(sizeof(float) * 2);
	if (!map->center)
		handle_error("Malloc failed.");
	map->center[0] = WIDTH / 2 - 1;
	map->center[1] = HEIGHT / 2 - 1;
	map->angle = 0;
	map->current_palette = 0;
	map->palette = create_palette();
	return (map);
}

t_coords	*process_row(char *buffer, int size_x, int y)
{
	char		**aux_buffers;
	t_coords	*row_x;
	int			x;

	x = -1;
	if (ft_countwords(buffer, ' ') != size_x)
		handle_error("Incorrect map format.");
	aux_buffers = ft_split(buffer, ' ');
	row_x = (t_coords *)malloc(sizeof(t_coords) * size_x);
	if (!row_x)
		handle_error("Malloc failed.");
	while (++x < size_x)
		row_x[x] = assign_coords(x, y, ft_atoi(aux_buffers[x]), 0.54);
	free_buffers(aux_buffers, size_x);
	return (row_x);
}

t_coords	**parse_map(int fd, int size_x, int size_y)
{
	t_coords	**map;
	char		*buffer;
	int			y;

	map = (t_coords **)malloc(sizeof(t_coords *) * size_y);
	if (!map)
		handle_error("Malloc failed.");
	buffer = get_next_line(fd);
	y = -1;
	while (buffer != NULL && ++y < size_y)
	{
		map[y] = process_row(buffer, size_x, y);
		buffer = get_next_line(fd);
	}
	if (buffer != NULL || y < size_y - 1)
		handle_error("Incorrect map format.");
	close(fd);
	return (add_scale(add_offset(map, size_x, size_y), size_x, size_y));
}

t_coords	assign_coords(int x, int y, int z, float alpha)
{
	t_coords	coordinates;

	coordinates.x = x;
	coordinates.y = y;
	coordinates.z = z;
	coordinates.iso_x = (x * cosf(alpha) \
				+ y * cosf(alpha + 2) \
				+ z * cosf(alpha - 2));
	coordinates.iso_y = (x * sinf(alpha) \
				+ y * sinf(alpha + 2) \
				+ z * sinf(alpha - 2));
	return (coordinates);
}

void	free_buffers(char **buffers, int size)
{
	int	i;

	i = -1;
	if (!buffers)
		return ;
	while (++i < size)
		free (buffers[i]);
	free (buffers);
}
