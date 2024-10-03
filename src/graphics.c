/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpenas-z <mpenas-z@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 12:58:23 by mpenas-z          #+#    #+#             */
/*   Updated: 2024/10/03 18:31:36 by archangelus      ###   ########.fr       */
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

void	paint_line(float *x, float *y, mlx_image_t *img)
{
	int		i;
	float	dx;
	float	dy;
	float	step;

	dx = fabs(x[1] - x[0]);
	dy = fabs(y[1] - y[0]);
	if(dx >= dy)
		step = dx;
	else
		step = dy;
	dx = dx/step;
	dy = dy/step;
	i = 0;
	while (i <= step)
	{
		mlx_put_pixel(img, x[0], y[0], 0xFFFFFFFF);
		x[0] += dx;
		y[0] += dy;
		i++;
	}
}

/*void	draw_lines(t_fdf_map *map, mlx_image_t *img)*/
/*{*/
/*	int		i;*/
/*	int		j;*/
/*	float	x[2];*/
/*	float	y[2];*/
/**/
/*	i = 0;*/
/*	j = map->total_size;*/
/*	while (i < map->total_size)*/
/*	{*/
/*		x[0] = map->isometric[0][i];*/
/*		x[1] = map->isometric[0][i];*/
/*		y[0] = map->isometric[1][j];*/
/*		y[1] = map->isometric[1][j - 1];*/
/*		paint_line(x, y, img);*/
/*		i++;*/
/*		j--;*/
/*	}*/
/*}*/

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
			ft_putstr_fd("\nFor i: ", 1);
			ft_putnbr_fd(i, 1);
			ft_putstr_fd("\nFor j: ", 1);
			ft_putnbr_fd(j, 1);
			ft_putstr_fd("\nZ: ", 1);
			ft_putnbr_fd(map->map[i][j].z, 1);
			/*ft_putstr_fd("\nIsometric Y: ", 1);*/
			/*ft_putnbr_fd(map->map[i][j]->iso_y, 1);*/
			ft_putstr_fd("\n", 1);
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
