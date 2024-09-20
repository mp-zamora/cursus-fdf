/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpenas-z <mpenas-z@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 12:58:23 by mpenas-z          #+#    #+#             */
/*   Updated: 2024/09/20 13:29:46 by mpenas-z         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

void	ft_hook(void *param)
{
	mlx_t* mlx;

	mlx = param;
	if (mlx_is_key_down(mlx, MLX_KEY_ESCAPE))
		mlx_close_window(mlx);
}

/*int32_t	init_graphics(int **map, int size_x, int size_y)*/
/*{*/
/*	mlx_t* mlx;*/
/*	mlx_image_t* img;*/
/**/
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
/*	return (EXIT_SUCCESS);*/
/*}*/
