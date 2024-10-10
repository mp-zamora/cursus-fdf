/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpenas-z <mpenas-z@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 18:48:38 by mpenas-z          #+#    #+#             */
/*   Updated: 2024/10/11 00:13:18 by archangelus      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

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

// The idea is to get the Z height of o and d points.
// Then, calculate the percent between those two points that x and y have.
// Then, calculate which color corresponds to o and which one to d.
// Then calculate the percent color for x and y between color_o and color_d.
float	get_z_percent(int z, int max_z, int min_z)
{
	int		dz;
	float	percent;
	
	dz = abs(max_z - min_z);
	percent = (z - min_z) / dz;
	return (percent);
}

// Here I SHOULD get the relative % from o to d.
float	get_od_percent(float x, float y, t_coords o, t_coords d)
{
	float	dx;
	float	dy;

	dx = d.x - o.x;
	dy = d.y - o.y;
	if (fabs(dx) > fabs(dy))
	{
		if (o.x != d.x)
			return ((x - o.x) / (d.x - o.x));
	}
	else
	{	
		if (o.y != d.y)
			return ((y - o.y) / (d.y - o.y));
	}
	return (0);
}

float get_percent(float x, float y, t_coords o, t_coords d, t_fdf_map *m)
{
	float	od_percent;
	float	o_percent;
	float	d_percent;
	float	final_percent;

	od_percent = get_od_percent(x, y, o, d);
	o_percent = get_z_percent(o.z, get_max_height(m).z, get_min_height(m).z);
	d_percent = get_z_percent(d.z, get_max_height(m).z, get_min_height(m).z);
	final_percent = ((o_percent - d_percent) * od_percent) + o_percent;
	return (final_percent);
}

t_coords	get_max_height(t_fdf_map *map)
{
	int			i;
	int			j;
	t_coords	max;

	i = 0;
	max.x = 0;
	max.y = 0;
	max.z = INT_MIN;
	max.iso_x = 0;
	max.iso_y = 0;
	while (i < map->size_y)
	{
		j = 0;
		while (j < map->size_x)
		{
			if (map->map[i][j].z > max.z)
				max = map->map[i][j];
			j++;
		}
		i++;
	}
	return (max);
}

t_coords	get_min_height(t_fdf_map *map)
{
	int			i;
	int			j;
	t_coords	min;

	i = 0;
	min.x = 0;
	min.y = 0;
	min.z = INT_MAX;
	min.iso_x = 0;
	min.iso_y = 0;
	while (i < map->size_y)
	{
		j = 0;
		while (j < map->size_x)
		{
			if (map->map[i][j].z < min.z)
				min = map->map[i][j];
			j++;
		}
		i++;
	}
	return (min);
}
