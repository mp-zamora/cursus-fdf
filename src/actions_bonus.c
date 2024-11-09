/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpenas-z <mpenas-z@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 12:56:56 by mpenas-z          #+#    #+#             */
/*   Updated: 2024/11/09 18:30:25 by mpenas-z         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

mlx_image_t	*add_zoom(float zoom, t_fdf_map **map)
{
	if ((*map)->projection != 0)
		return (render_map((*map)));
	(*map)->map = recalculate_map((*map));
	(*map)->zoom = zoom;
	(*map)->map = apply_zoom((*map)->map, (*map)->size_x, \
					(*map)->size_y, (*map)->zoom);
	center_map(map);
	return (render_map((*map)));
}

mlx_image_t	*add_translation(float tx, float ty, t_fdf_map **map)
{
	if ((*map)->projection != 0)
		return (render_map((*map)));
	(*map)->translation[0] += (WIDTH * tx);
	(*map)->translation[1] += (HEIGHT * ty);
	add_x_offset(map, (WIDTH * tx));
	add_y_offset(map, (HEIGHT * ty));
	return (render_map((*map)));
}

mlx_image_t	*add_rotation(float theta, t_fdf_map **map)
{
	int	i;
	int	j;

	if ((*map)->projection != 0)
		return (render_map((*map)));
	i = -1;
	(*map)->theta += theta;
	theta = (*map)->theta;
	while (++i < (*map)->size_y)
	{
		j = -1;
		while (++j < (*map)->size_x)
		{
			(*map)->map[i][j].x = (*map)->original[i][j].x * cosf(theta) \
				- (*map)->original[i][j].y * sinf(theta);
			(*map)->map[i][j].y = (*map)->original[i][j].x * sinf(theta) \
				+ (*map)->original[i][j].y * cosf(theta);
		}
	}
	(*map)->map = recalculate_map((*map));
	(*map)->map = apply_zoom((*map)->map, (*map)->size_x, \
						(*map)->size_y, (*map)->zoom);
	center_map(map);
	return (render_map((*map)));
}

void	apply_projection_change(int projection, t_fdf_map **map)
{
	int	i;
	int	j;

	i = -1;
	while (++i < (*map)->size_y)
	{
		j = -1;
		while (++j < (*map)->size_x)
		{
			if (projection == 1 || projection == 2)
				(*map)->map[i][j].iso_x = (*map)->original[i][j].x;
			if (projection == 1)
				(*map)->map[i][j].iso_y = (*map)->original[i][j].y;
			if (projection == 2 || projection == 3)
				(*map)->map[i][j].iso_y = (-1) * (*map)->original[i][j].z;
			if (projection == 3)
				(*map)->map[i][j].iso_x = (*map)->original[i][j].y;
		}
	}
	(*map)->map = add_offset((*map)->map, (*map)->size_x, (*map)->size_y);
}

mlx_image_t	*perspective_projection(int projection, t_fdf_map **map)
{
	(*map)->projection = projection;
	if (projection == 0)
	{
		(*map)->map = recalculate_map((*map));
		(*map)->map = apply_zoom((*map)->map, (*map)->size_x, \
							(*map)->size_y, (*map)->zoom);
		center_map(map);
		return (render_map((*map)));
	}
	else
		apply_projection_change(projection, map);
	(*map)->map = add_scale((*map)->map, (*map)->size_x, (*map)->size_y);
	center_map(map);
	return (render_map((*map)));
}
