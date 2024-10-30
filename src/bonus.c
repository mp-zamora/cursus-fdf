/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpenas-z <mpenas-z@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 12:56:56 by mpenas-z          #+#    #+#             */
/*   Updated: 2024/10/30 21:21:49 by mpenas-z         ###   ########.fr       */
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
