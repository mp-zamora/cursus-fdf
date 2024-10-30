/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpenas-z <mpenas-z@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 18:48:38 by mpenas-z          #+#    #+#             */
/*   Updated: 2024/10/30 20:37:17 by mpenas-z         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

// REMOVE
#include <stdio.h>
// REMOVE

float	*get_max_coords(t_coords **map, int size_x, int size_y)
{
	int		i;
	int		j;
	float	*max_coords;

	i = 0;
	max_coords = (float *)malloc(sizeof(float) * 2);
	if (!max_coords)
		handle_error("Malloc failed.");
	max_coords[0] = 0;
	max_coords[1] = 0;
	while (i < size_y)
	{
		j = 0;
		while (j < size_x)
		{
			if (map[i][j].iso_x > max_coords[0])
				max_coords[0] = map[i][j].iso_x;
			if (map[i][j].iso_y > max_coords[1])
				max_coords[1] = map[i][j].iso_y;
			j++;
		}
		i++;
	}
	return (max_coords);
}

int	get_max_height(t_fdf_map *map)
{
	int			i;
	int			j;
	int			max;

	i = 0;
	max = INT_MIN;
	while (i < map->size_y)
	{
		j = 0;
		while (j < map->size_x)
		{
			if (map->map[i][j].z > max)
				max = map->map[i][j].z;
			j++;
		}
		i++;
	}
	return (max);
}

int	get_min_height(t_fdf_map *map)
{
	int			i;
	int			j;
	int			min;

	i = 0;
	min = INT_MAX;
	while (i < map->size_y)
	{
		j = 0;
		while (j < map->size_x)
		{
			if (map->map[i][j].z < min)
				min = map->map[i][j].z;
			j++;
		}
		i++;
	}
	return (min);
}

int	get_max_x(int fd)
{
	char	*buffer;

	buffer = get_next_line(fd);
	if (!buffer)
		return (0);
	free (buffer);
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
		free (buffer);
		buffer = get_next_line(fd);
	}
	if (buffer)
		free (buffer);
	close (fd);
	return (y);
}
