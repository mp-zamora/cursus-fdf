/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpenas-z <mpenas-z@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 11:38:49 by mpenas-z          #+#    #+#             */
/*   Updated: 2024/10/03 19:54:41 by archangelus      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

int	get_max_x(int fd)
{
	char	*buffer;

	buffer = get_next_line(fd);
	if (!buffer)
		return (0);
	close (fd);
	return (ft_countwords(buffer, ' '));
}

int	get_max_y(int fd)
{
	char	*buffer;
	int		y;

	y = 0;
	buffer = get_next_line(fd);
	while (buffer)
	{
		y++;
		buffer = get_next_line(fd);
	}
	close (fd);
	return (y);
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

t_fdf_map	*init_map(char *file)
{
	t_fdf_map	*map;

	ft_putstr_fd("Initializing map...\n", 1);
	map = (t_fdf_map *)malloc(sizeof(t_fdf_map));
	if (!map)
		handle_error("Map malloc failed.");
	map->size_x = get_max_x(open_file(file));
	map->size_y = get_max_y(open_file(file));
	map->map = parse_map(open_file(file), map->size_x, map->size_y);
	if (!map)
		handle_error("Map parsing failed.");
	map->total_size = map->size_x * map->size_y;
	map->max_coords = get_max_coords(map->map, map->size_x, map->size_y);
	ft_putstr_fd("Initialized succesfully!\n", 1);
	return (map);
}

t_coords	**add_offset(t_coords **map, int size_x, int size_y)
{
	int		i;
	int		j;
	float	*offset;

	offset = get_offset(map, size_x, size_y);
	i = 0;
	while (i < size_y)
	{
		j = 0;
		while (j < size_x)
		{
			map[i][j].iso_x += offset[0] + 10;
			map[i][j].iso_y += offset[1] + 10;
			j++;
		}
		i++;
	}
	free (offset);
	return (map);
}

t_coords	**parse_map(int fd, int size_x, int size_y)
{
	t_coords	**map;
	char		*buffer;
	char		**aux_buffers;
	int			x;
	int			y;

	map = (t_coords **)malloc(sizeof(t_coords *) * size_y);
	if (!map)
		handle_error("Points map allocation failed.");
	buffer = get_next_line(fd);
	y = -1;
	while (buffer != NULL && ++y < size_y)
	{
		x = -1;
		if (ft_countwords(buffer, ' ') != size_x)
			handle_error("Size_x missmatch.");
		aux_buffers = ft_split(buffer, ' ');
		map[y] = (t_coords *)malloc(sizeof(t_coords) * size_x);
		if (!map[y])
			handle_error("map[y] malloc failed.");
		while (++x < size_x)
			map[y][x] = assign_coords(x, y, ft_atoi(aux_buffers[x]), 0.54, 15);
		free_buffers(aux_buffers, size_x);
		buffer = get_next_line(fd);
	}
	if (buffer != NULL || y < size_y - 1)
		handle_error("Buffer != NULL or y > 0 at the end of parsing.");
	close(fd);
	return (add_offset(map, size_x, size_y));
}

t_coords	assign_coords(int x, int y, int z, float alpha, float scale)
{
	t_coords coordinates;

	coordinates.x = x;
	coordinates.y = y;
	coordinates.z = z;
	coordinates.iso_x = (x * cosf(alpha) \
				+ y * cosf(alpha + 2) \
				+ z * cosf(alpha - 2)) * scale;
	coordinates.iso_y = (x * sinf(alpha) \
				+ y * sinf(alpha + 2) \
				+ z * sinf(alpha - 2)) * scale;
	return (coordinates);
}

float	*get_offset(t_coords **map, int size_x, int size_y)
{
	int		i;
	int		j;
	float	*offset;

	i = 0;
	offset = (float *)malloc(sizeof(float) * 2);
	if (!offset)
		handle_error("Offset malloc failed.");
	offset[0] = 0;
	offset[1] = 0;
	while (i < size_y)
	{
		j = 0;
		while (j < size_x)
		{
			if (map[i][j].iso_x < 0 && fabsf(map[i][j].iso_x) > offset[0])
				offset[0] = fabsf(map[i][j].iso_x);
			if (map[i][j].iso_y < 0 && fabsf(map[i][j].iso_y) > offset[1])
				offset[1] = fabsf(map[i][j].iso_y); 
			j++;
		}
		i++;
	}
	return (offset);
}
