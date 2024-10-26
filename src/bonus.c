/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpenas-z <mpenas-z@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 12:56:56 by mpenas-z          #+#    #+#             */
/*   Updated: 2024/10/26 11:25:28 by mpenas-z         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

mlx_image_t	*add_zoom(float zoom, t_fdf_map **map)
{
	(*map)->map = recalculate_map((*map));
	(*map)->zoom = zoom;
	(*map)->map = apply_zoom((*map)->map, (*map)->size_x, \
						  (*map)->size_y, (*map)->zoom);
	center_map(map);
	return (render_map((*map)));
}

mlx_image_t	*add_translation(float tx, float ty, t_fdf_map **map)
{
	(*map)->center[0] += (WIDTH * tx);
	(*map)->center[1] += (HEIGHT * ty);
	add_x_offset(map, (WIDTH * tx));
	add_y_offset(map, (HEIGHT * ty));
	return (render_map((*map)));
}

mlx_image_t	*add_rotation(float degrees, t_fdf_map **map)
{
	(*map)->radians += (degrees * PI) / 180;
	(*map)->map = recalculate_map((*map));
	center_map(map);
	(*map)->map = apply_zoom((*map)->map, (*map)->size_x, \
						(*map)->size_y, (*map)->zoom);
	return (render_map((*map)));
}

void	center_map(t_fdf_map **map)
{
	float	*max_coords;
	float	adjustment[2];

	adjustment[0] = 0;
	adjustment[1] = 1;
	max_coords = get_max_coords((*map)->map, (*map)->size_x, (*map)->size_y);
	if ((max_coords[0] / 2 - 1) != (*map)->center[0])
		adjustment[0] = (*map)->center[0] - (max_coords[0] / 2 - 1);
	if ((max_coords[1] / 2 - 1) != (*map)->center[1])
		adjustment[1] = (*map)->center[1] - (max_coords[1] / 2 - 1);
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
