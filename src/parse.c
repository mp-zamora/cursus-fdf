/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpenas-z <mpenas-z@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 11:38:49 by mpenas-z          #+#    #+#             */
/*   Updated: 2024/11/09 17:38:24 by mpenas-z         ###   ########.fr       */
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
	map->theta = 0.1;
	map->map = parse_map(open_file(file), map->size_x, map->size_y);
	if (!map->map)
		handle_error("Parsing failed.");
	map->original = parse_map(open_file(file), map->size_x, map->size_y);
	if (!map->original)
		handle_error("Parsing failed.");
	map->scale = get_scale(map->map, map->size_x, map->size_y);
	map->map = apply_zoom(map->map, map->size_x, map->size_y, map->scale);
	map->original = apply_zoom(map->original, map->size_x, \
						map->size_y, map->scale);
	map->file = file;
	assign_data(&map);
	return (map);
}

void	assign_data(t_fdf_map **fdf_map)
{
	t_fdf_map	*map;

	map = (*fdf_map);
	map->total_size = map->size_x * map->size_y;
	map->max_coords = get_max_coords(map->map, map->size_x, map->size_y);
	map->max_z = get_max_height(map);
	map->min_z = get_min_height(map);
	map->projection = 0;
	map->zoom = 1;
	map->center = (float *)malloc(sizeof(float) * 2);
	if (!map->center)
		handle_error("Malloc failed.");
	map->center[0] = WIDTH / 2 - 1;
	map->center[1] = HEIGHT / 2 - 1;
	map->current_palette = 0;
	map->palette = create_palette();
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
		row_x[x] = assign_coords(x, y, ft_atoi(aux_buffers[x]));
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
		free (buffer);
		buffer = get_next_line(fd);
	}
	if (buffer != NULL || y < size_y - 1)
		handle_error("Incorrect map format.");
	if (buffer)
		free (buffer);
	close(fd);
	return (add_offset(map, size_x, size_y));
}

t_coords	assign_coords(int x, int y, int z)
{
	t_coords	coordinates;

	coordinates.x = x;
	coordinates.y = y;
	coordinates.z = z;
	coordinates.iso_x = x - y;
	coordinates.iso_y = (x + y) / 2.0 - z;
	return (coordinates);
}
