/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpenas-z <mpenas-z@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 11:38:49 by mpenas-z          #+#    #+#             */
/*   Updated: 2024/09/29 17:40:09 by mpenas-z         ###   ########.fr       */
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
	map->isometric = convert_to_iso(map->map, map->size_x, map->size_y);
	/*else*/
	/*	print_map(map->map, map->size_y, map->size_x);*/
	map->gradient = fill_gradient();
	ft_putstr_fd("Initialized succesfully!\n", 1);
	return (map);
}

int	**parse_map(int fd, int size_x, int size_y)
{
	int		**map;
	char	*buffer;
	char	**aux_buffers;
	int		x;
	int		y;

	map = (int **)malloc(sizeof(int *) * size_y);
	if (!map)
		handle_error("Points map allocation failed.");
	buffer = get_next_line(fd);
	y = size_y;
	while (buffer != NULL && y-- > 0)
	{
		x = -1;
		if (ft_countwords(buffer, ' ') != size_x)
			handle_error("Size_x missmatch.");
		aux_buffers = ft_split(buffer, ' ');
		map[y] = (int *)malloc(sizeof(int) * size_x);
		if (!map[y])
			handle_error("map[y] malloc failed.");
		while (++x < size_x)
			map[y][x] = ft_atoi(aux_buffers[x]);
		free_buffers(aux_buffers, size_x);
		buffer = get_next_line(fd);
	}
	if (buffer != NULL || y > 0)
		handle_error("Buffer != NULL or y > 0 at the end of parsing.");
	close(fd);
	return (map);
}
