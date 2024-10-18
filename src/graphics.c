/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpenas-z <mpenas-z@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 12:58:23 by mpenas-z          #+#    #+#             */
/*   Updated: 2024/10/18 21:58:48 by mpenas-z         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

void	close_hook(void *param)
{
	t_fdf_map **master_map;
	t_fdf_map *map;

	master_map = param;
	map = (*master_map);
	if (mlx_is_key_down(map->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(map->mlx);
	if (mlx_is_key_down(map->mlx, MLX_KEY_SPACE))
	{
		(*master_map)->colors[0] = 0x4997d0;
		(*master_map)->colors[1] = 0xd08249;
		render_map((*master_map));
	}
}

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
	coords[0] = o.iso_x;
	coords[1] = o.iso_y;
	i = -1;
	while (++i <= step)
	{
		color = get_color(coords, o, d, m);
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

	aux_img = mlx_new_image(map->mlx, WIDTH, HEIGHT);
	if (!aux_img)
	{
		mlx_close_window(map->mlx);
		handle_error("MLX failed.");
	}
	draw_lines(map, aux_img);
	if (map->img)
		mlx_delete_image(map->mlx, map->img);
	mlx_image_to_window(map->mlx, aux_img, 0, 0);
	return (aux_img);
}
