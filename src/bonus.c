/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpenas-z <mpenas-z@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 12:56:56 by mpenas-z          #+#    #+#             */
/*   Updated: 2024/10/20 10:28:00 by mpenas-z         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

void	add_zoom(float zoom, t_fdf_map **map)
{
	int	i;
	int	j;

	i = -1;
	(*map)->map = parse_map(open_file((*map)->file), \
					(*map)->size_x, (*map)->size_y);
	(*map)->zoom = zoom;
	while (++i < (*map)->size_y)
	{
		j = -1;
		while (++j < (*map)->size_x)
		{
			(*map)->map[i][j].iso_x *= zoom;
			(*map)->map[i][j].iso_y *= zoom;
		}
	}
	center_map(map);
}

void	center_map(t_fdf_map **map)
{
	float	mid_x;
	float	mid_y;
	float	*max_coords;
	float	adjustment[2];

	mid_x = WIDTH / 2 - 1;
	mid_y = HEIGHT / 2 - 1;
	adjustment[0] = 0;
	adjustment[1] = 1;
	max_coords = get_max_coords((*map)->map, (*map)->size_x, (*map)->size_y);
	if ((max_coords[0] / 2 - 1) != mid_x)
		adjustment[0] = mid_x - (max_coords[0] / 2 - 1);
	if ((max_coords[1] / 2 - 1) != mid_y)
		adjustment[1] = mid_y - (max_coords[1] / 2 - 1);
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
