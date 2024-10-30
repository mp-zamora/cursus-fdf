/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpenas-z <mpenas-z@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 17:51:30 by mpenas-z          #+#    #+#             */
/*   Updated: 2024/10/30 21:24:47 by mpenas-z         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

float	get_z_percent(int z, int max_z, int min_z)
{
	float	percent;

	if (max_z == min_z)
		return (0);
	percent = (float)(z - min_z) / (float)(max_z - min_z);
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

float	get_percent(float coords[2], t_coords o, t_coords d, t_fdf_map *m)
{
	float	od_percent;
	float	o_percent;
	float	d_percent;
	float	final_percent;

	od_percent = get_od_percent(coords[0], coords[1], o, d);
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
		final_percent = (d_percent - o_percent) * (1 - od_percent) + o_percent;
	}
	return (final_percent);
}

float	*get_min_coords(t_coords **map, int size_x, int size_y)
{
	int		i;
	int		j;
	float	*min_coords;

	i = 0;
	min_coords = get_max_coords(map, size_x, size_y);
	while (i < size_y)
	{
		j = 0;
		while (j < size_x)
		{
			if (map[i][j].iso_x < min_coords[0])
				min_coords[0] = map[i][j].iso_x;
			if (map[i][j].iso_y < min_coords[1])
				min_coords[1] = map[i][j].iso_y;
			j++;
		}
		i++;
	}
	return (min_coords);
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
