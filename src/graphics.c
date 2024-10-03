/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpenas-z <mpenas-z@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 12:58:23 by mpenas-z          #+#    #+#             */
/*   Updated: 2024/10/03 12:11:51 by mpenas-z         ###   ########.fr       */
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

void	draw_map(t_fdf_map *map, mlx_image_t *img)
{
	int	i;
	mlx_image_t *test;

	/* The 2 lines below are in place to avoid warnings */
	test = img;
	img = test;
	/* Prints the isometric coordinates */
	ft_putstr_fd("Painting pixels...", 1);
	i = -1;
	while (++i < map->total_size)
	{
		/* Here I should paint each correspondant pixel */
		/*ft_putstr_fd("\nFor i: ", 1);*/
		/*ft_putnbr_fd(i, 1);*/
		/*ft_putstr_fd("\nIsometric X: ", 1);*/
		/*ft_putnbr_fd(map->isometric[0][i], 1);*/
		/*ft_putstr_fd("\nIsometric Y: ", 1);*/
		/*ft_putnbr_fd(map->isometric[1][i], 1);*/
		/*ft_putstr_fd("\n", 1);*/
		mlx_put_pixel(img, map->isometric[0][i], map->isometric[1][i], 0xFFFFFFFF);
	}
	ft_putstr_fd("Pixels painted successfully!\n", 1);
	/* Here I should pass img to window */
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
