/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpenas-z <mpenas-z@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 12:58:23 by mpenas-z          #+#    #+#             */
/*   Updated: 2024/10/08 19:23:15 by mpenas-z         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

void	ft_hook(void *param)
{
	mlx_t	*mlx;

	mlx = param;
	if (mlx_is_key_down(mlx, MLX_KEY_ESCAPE))
		mlx_close_window(mlx);
}

void	paint_line(t_coords o, t_coords d, mlx_image_t *img, uint32_t c)
{
	int			i;
	float		dx;
	float		dy;
	float		step;
	float		coords[2];

	dx = d.iso_x - o.iso_x;
	dy = d.iso_y - o.iso_y;
	if(fabs(dx) >= fabs(dy))
		step = fabs(dx);
	else
		step = fabs(dy);
	dx = dx / step;
	dy = dy / step;
	coords[0] = o.iso_x;
	coords[1] = o.iso_y;
	i = 0;
	while (i <= step)
	{
		if (c == 0)
			c = get_color(coords[0], coords[1], o, d);
		mlx_put_pixel(img, coords[0], coords[1], c);
		coords[0] += dx;
		coords[1] += dy;
		i++;
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
				paint_line(map->map[i][j],map->map[i][j + 1], img, 0);
			if (i + 1 < map->size_y)
				paint_line(map->map[i][j], map->map[i + 1][j], img, 0);
			j++;
		}
		i++;
	}
}

void	draw_map(t_fdf_map *map, mlx_image_t *img)
{
	int			i;
	int			j;

	i = 0;
	while (i < map->size_y)
	{
		j = 0;
		while (j < map->size_x)
		{
			mlx_put_pixel(img, map->map[i][j].iso_x, \
				 map->map[i][j].iso_y, 0xFFFFFFFF);
			j++;
		}
		i++;
	}
	draw_lines(map, img);
}
