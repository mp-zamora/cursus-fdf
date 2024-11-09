/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpenas-z <mpenas-z@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 12:58:23 by mpenas-z          #+#    #+#             */
/*   Updated: 2024/11/09 17:42:10 by mpenas-z         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

void	paint_line(t_coords o, t_coords d, mlx_image_t *img, t_fdf_map *m)
{
	int			i;
	float		diff[2];
	float		step;
	float		coords[2];
	uint32_t	color;

	diff[0] = d.iso_x - o.iso_x;
	diff[1] = d.iso_y - o.iso_y;
	if (fabs(diff[0]) >= fabs(diff[1]))
		step = fabs(diff[0]);
	else
		step = fabs(diff[1]);
	diff[0] = diff[0] / step;
	diff[1] = diff[1] / step;
	ft_memcpy(coords, (float [2]){o.iso_x, o.iso_y}, sizeof(coords));
	i = -1;
	while (++i <= step)
	{
		color = get_color(coords, o, d, m);
		if (coords[0] > 0 && coords[1] > 0
			&& coords[0] < WIDTH - 1 && coords[1] < HEIGHT - 1)
			mlx_put_pixel(img, coords[0], coords[1], color);
		coords[0] += diff[0];
		coords[1] += diff[1];
	}
}

void	draw_lines(t_fdf_map *map, mlx_image_t *img)
{
	int		i;
	int		j;

	i = 0;
	while (i < map->size_y)
	{
		j = 0;
		while (j < map->size_x)
		{
			if (j + 1 < map->size_x)
				paint_line(map->map[i][j], map->map[i][j + 1], img, map);
			if (i + 1 < map->size_y)
				paint_line(map->map[i][j], map->map[i + 1][j], img, map);
			j++;
		}
		i++;
	}
}

mlx_image_t	*render_map(t_fdf_map *map)
{
	mlx_image_t	*aux_img;

	if (map->img)
		mlx_delete_image(map->mlx, map->img);
	aux_img = mlx_new_image(map->mlx, WIDTH, HEIGHT);
	if (!aux_img)
	{
		mlx_close_window(map->mlx);
		handle_error("MLX failed.");
	}
	draw_lines(map, aux_img);
	mlx_image_to_window(map->mlx, aux_img, 0, 0);
	return (aux_img);
}
