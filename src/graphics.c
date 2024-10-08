/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpenas-z <mpenas-z@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 12:58:23 by mpenas-z          #+#    #+#             */
/*   Updated: 2024/10/08 12:54:31 by mpenas-z         ###   ########.fr       */
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

void	paint_line(t_coords origin, t_coords destination, mlx_image_t *img, uint32_t color)
{
	int		i;
	float	dx;
	float	dy;
	float	step;

	dx = fabs(destination.iso_x - origin.iso_x);
	dy = fabs(destination.iso_y - origin.iso_y);
	if(dx >= dy)
		step = dx;
	else
		step = dy;
	dx = dx/step;
	dy = dy/step;
	i = 0;
	while (i <= step)
	{
		mlx_put_pixel(img, origin.iso_x, origin.iso_y, color);
		origin.iso_x += dx;
		origin.iso_y += dy;
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
			//DEBUG
			printf("Origin Coordinates: i = %d, j = %d; X = %f, Y = %f;\n", \
				i, j, map->map[i][j].iso_x, map->map[i][j].iso_y);
			//DEBUG
			if (j + 1 < map->size_x)
			{
				paint_line(map->map[i][j],map->map[i][j + 1], img, 0xFF0000FF);
				printf("Line Destination Coordinates: i = %d, j = %d; X = %f, Y = %f;\n", \
					i, j + 1, map->map[i][j + 1].iso_x, map->map[i][j + 1].iso_y);
			}
			if (i + 1 < map->size_y)
			{
				paint_line(map->map[i][j], map->map[i + 1][j], img, 0x00FFFFFF);
				printf("Column Destination Coordinates: i = %d, j = %d; X = %f, Y = %f;\n", \
					i + 1, j, map->map[i + 1][j].iso_x, map->map[i + 1][j].iso_y);
			}
			j++;
		}
		i++;
	}
}

void	draw_map(t_fdf_map *map, mlx_image_t *img)
{
	int			i;
	int			j;

	ft_putstr_fd("Painting pixels...\n", 1);
	i = 0;
	while (i < map->size_y)
	{
		j = 0;
		while (j < map->size_x)
		{
			/* Here I should paint each correspondant pixel */
			/*ft_putstr_fd("\nFor i: ", 1);*/
			/*ft_putnbr_fd(i, 1);*/
			/*ft_putstr_fd("\nFor j: ", 1);*/
			/*ft_putnbr_fd(j, 1);*/
			/*ft_putstr_fd("\nZ: ", 1);*/
			/*ft_putnbr_fd(map->map[i][j].z, 1);*/
			/*ft_putstr_fd("\n", 1);*/
			/*printf("ISOX: %f\n", map->map[i][j].iso_x);*/
			/*printf("ISOY: %f\n", map->map[i][j].iso_y);*/
			mlx_put_pixel(img, map->map[i][j].iso_x, \
				 map->map[i][j].iso_y, 0xFFFFFFFF);
			j++;
		}
		i++;
	}
	/*draw_lines(map, img);*/
	ft_putstr_fd("Pixels painted successfully!\n", 1);
	/* Here I should pass img to window */
}
