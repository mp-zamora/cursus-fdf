/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpenas-z <mpenas-z@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 12:58:23 by mpenas-z          #+#    #+#             */
/*   Updated: 2024/09/20 18:50:20 by mpenas-z         ###   ########.fr       */
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

/*int32_t	init_graphics(int **map, int size_x, int size_y)*/
/*{*/
/*	mlx_t* mlx;*/
/*	mlx_image_t* img;*/
/**/
/*	int aux = size_x + 1;*/
/*	size_x = aux - 1;*/
/*	mlx = mlx_init(WIDTH, HEIGHT, "FdF", true);*/
/*	if (!mlx)*/
/*		handle_error();*/
/*	img = mlx_new_image(mlx, WIDTH, HEIGHT);*/
/*	if (!img || (mlx_image_to_window(mlx, img, 0, 0) < 0))*/
/*	{*/
/*		mlx_close_window(mlx);*/
/*		handle_error();*/
/*	}*/
/*	mlx_loop_hook(mlx, ft_hook, mlx);*/
/*	mlx_loop(mlx);*/
/*	mlx_terminate(mlx);*/
/*	free_fdf_map(map, size_y);*/
/*	return (EXIT_SUCCESS);*/
/*}*/
