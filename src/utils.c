/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpenas-z <mpenas-z@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 18:48:38 by mpenas-z          #+#    #+#             */
/*   Updated: 2024/10/15 19:43:41 by mpenas-z         ###   ########.fr       */
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

float	get_z_percent(int z, int max_z, int min_z)
{
	int		dz;
	float	percent;
	
	if (max_z == min_z)
		return (0);
	dz = abs(max_z - min_z);
	percent = (z - min_z) / dz;
	return (percent);
}

float	get_od_percent(float x, float y, t_coords o, t_coords d)
{
	float	dx;
	float	dy;

	dx = d.iso_x - o.iso_x;
	dy = d.iso_y - o.iso_y;
	if (fabs(dx) > fabs(dy))
	{
		if (x == o.iso_x)
			return (0);
		if (d.iso_x > o.iso_x)
			return ((x - o.iso_x) / (d.iso_x - o.iso_x));
		else if (o.iso_x > d.iso_x)
			return ((o.iso_x - x) / (o.iso_x - d.iso_x));
	}
	else
	{
		if (y == o.iso_y)
			return (0);
		if (d.iso_y > o.iso_y)
			return ((y - o.iso_y) / (d.iso_y - o.iso_y));
		else if (o.iso_y > d.iso_y)
			return ((o.iso_y - y) / (o.iso_y - d.iso_y));
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
	if (d.z > o.z)
	{
		o_percent = get_z_percent(o.z, m->max_z, m->min_z);
		d_percent = get_z_percent(d.z, m->max_z, m->min_z);
		final_percent = ((d_percent - o_percent) * (od_percent)) + o_percent;
	}
	else
	{
		o_percent = get_z_percent(d.z, m->max_z, m->min_z);
		d_percent = get_z_percent(o.z, m->max_z, m->min_z);
		final_percent = ((d_percent - o_percent) * (1 - od_percent)) + o_percent;
	}
	return (final_percent);
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
