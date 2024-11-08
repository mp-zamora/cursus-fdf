/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpenas-z <mpenas-z@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 12:56:56 by mpenas-z          #+#    #+#             */
/*   Updated: 2024/11/08 20:41:57 by archangelus      ###   ########.fr       */
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

mlx_image_t	*add_rotation(float theta, t_fdf_map **map)
{
	int	i;
	int	j;

	i = -1;
	(*map)->theta += theta;
	theta = (*map)->theta;
	while (++i < (*map)->size_y)
	{
		j = -1;
		while (++j < (*map)->size_x)
		{
			(*map)->map[i][j].x = (*map)->original[i][j].x * cosf(theta) - (*map)->original[i][j].y * sinf(theta);
			(*map)->map[i][j].y = (*map)->original[i][j].x * sinf(theta) + (*map)->original[i][j].y * cosf(theta);
		}
	}
	(*map)->map = recalculate_map((*map));
	(*map)->map = apply_zoom((*map)->map, (*map)->size_x, \
						(*map)->size_y, (*map)->zoom);
	center_map(map);
	return (render_map((*map)));
}

mlx_image_t *perspective_projection(int projection, t_fdf_map **map)
{
	int	i;
	int	j;

	i = -1;
	while (++i < (*map)->size_y)
	{
		j = -1;
		while (++j < (*map)->size_x)
		{
			if (projection == 1)
			{
				(*map)->map[i][j].iso_x = (*map)->original[i][j].x;
				(*map)->map[i][j].iso_y = (*map)->original[i][j].y;
			}
			else if (projection == 2)
			{
				(*map)->map[i][j].iso_x = (*map)->original[i][j].x;
				(*map)->map[i][j].iso_y = (*map)->original[i][j].z;
			}
			else if (projection == 3)
			{
				(*map)->map[i][j].iso_x = (*map)->original[i][j].y;
				(*map)->map[i][j].iso_y = (*map)->original[i][j].z;
			}
		}
	}
	(*map)->map = add_scale((*map)->map, (*map)->size_x, (*map)->size_y);
	return (render_map((*map)));
}
