/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpenas-z <mpenas-z@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 21:21:14 by mpenas-z          #+#    #+#             */
/*   Updated: 2024/11/09 18:31:44 by mpenas-z         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

void	center_map(t_fdf_map **map)
{
	float	*max_coords;
	float	center[2];
	float	adjustment[2];

	center[0] = (WIDTH / 2) - 1 + (*map)->translation[0];
	center[1] = (HEIGHT / 2) - 1 + (*map)->translation[1];
	if ((*map)->projection != 0)
	{
		center[0] = WIDTH / 2 - 1;
		center[1] = HEIGHT / 2 - 1;
	}
	adjustment[0] = 0;
	adjustment[1] = 1;
	max_coords = get_max_coords((*map)->map, (*map)->size_x, (*map)->size_y);
	if ((max_coords[0] / 2 - 1) != center[0])
		adjustment[0] = center[0] - (max_coords[0] / 2 - 1);
	if ((max_coords[1] / 2 - 1) != center[1])
		adjustment[1] = center[1] - (max_coords[1] / 2 - 1);
	if (adjustment[0] != 0)
		add_x_offset(map, adjustment[0]);
	if (adjustment[1] != 0)
		add_y_offset(map, adjustment[1]);
	free (max_coords);
}

void	add_x_offset(t_fdf_map **map, float offset)
{
	int	i;
	int	j;

	i = -1;
	while (++i < (*map)->size_y)
	{
		j = -1;
		while (++j < (*map)->size_x)
			(*map)->map[i][j].iso_x += offset;
	}
}

void	add_y_offset(t_fdf_map **map, float offset)
{
	int	i;
	int	j;

	i = -1;
	while (++i < (*map)->size_y)
	{
		j = -1;
		while (++j < (*map)->size_x)
			(*map)->map[i][j].iso_y += offset;
	}
}

t_coords	**recalculate_map(t_fdf_map *map)
{
	int	i;
	int	j;

	i = -1;
	while (++i < map->size_y)
	{
		j = -1;
		while (++j < map->size_x)
		{
			map->map[i][j] = assign_coords(map->map[i][j].x, map->map[i][j].y, \
								map->map[i][j].z);
		}
	}
	map->map = apply_zoom(add_offset(map->map, map->size_x, map->size_y), \
					map->size_x, map->size_y, map->scale);
	return (map->map);
}
