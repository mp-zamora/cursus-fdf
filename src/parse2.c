/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpenas-z <mpenas-z@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 16:12:39 by mpenas-z          #+#    #+#             */
/*   Updated: 2024/10/08 16:16:28 by mpenas-z         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

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

float	*get_offset(t_coords **map, int size_x, int size_y)
{
	int		i;
	int		j;
	float	*offset;

	i = 0;
	offset = (float *)malloc(sizeof(float) * 2);
	if (!offset)
		handle_error("Malloc failed.");
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

t_coords	**add_scale(t_coords **map, int size_x, int size_y)
{
	int		i;
	int		j;
	float	scale;

	scale = get_scale(map, size_x, size_y);
	i = 0;
	while (i < size_y)
	{
		j = 0;
		while (j < size_x)
		{
			map[i][j].iso_x *= scale;
			map[i][j].iso_y *= scale;
			j++;
		}
		i++;
	}
	return (map);
}

float	get_scale(t_coords **map, int size_x, int size_y)
{
	float	scale;
	float	*max_coords;

	scale = 1;
	max_coords = get_max_coords(map, size_x, size_y);
	if (WIDTH / max_coords[0] < HEIGHT / max_coords[1])
		scale = WIDTH / max_coords[0];
	else
		scale = HEIGHT / max_coords[1];
	free (max_coords);
	return (scale * 0.95);
}
