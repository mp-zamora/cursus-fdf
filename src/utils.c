/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpenas-z <mpenas-z@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 18:48:38 by mpenas-z          #+#    #+#             */
/*   Updated: 2024/10/08 19:16:06 by mpenas-z         ###   ########.fr       */
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

float	get_percent(float x, float y, t_coords o, t_coords d)
{
	float	dx;
	float	dy;

	dx = d.x - o.x;
	dy = d.y - o.y;
	if (fabs(dx) > fabs(dy))
	{
		if (o.x != d.x)
			return (((x - o.x) / (d.x - o.x)));
	}
	else
	{	
		if (o.y != d.y)
			return (((y - o.y) / (d.y - o.y)));
	}
	return (0);
}

t_coords	get_max_height(t_coords **map, int size_x, int size_y)
{
	int			i;
	int			j;
	t_coords	max;

	i = 0;
	max.x = 0;
	max.y = 0;
	max.z = 0;
	max.iso_x = 0;
	max.iso_y = 0;
	while (i < size_y)
	{
		j = 0;
		while (j < size_x)
		{
			if (map[i][j].z > max.z)
				max = map[i][j];
			j++;
		}
	}
	return (max);
}
