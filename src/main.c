/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpenas-z <mpenas-z@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 14:27:02 by mpenas-z          #+#    #+#             */
/*   Updated: 2024/10/08 16:16:54 by mpenas-z         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

void	handle_error(char *message)
{
	ft_putstr_fd("Error: ", 2);
	if (message)
		ft_putstr_fd(message, 2);
	ft_putstr_fd("\n", 2);
	exit(2);
}

int	open_file(char *file)
{
	int	fd;

	fd = open(file, O_RDONLY);
	if (fd == -1)
		handle_error("Failure opening file.");
	return (fd);
}

void	print_map(int **map, int size_y, int size_x)
{
	int	y;
	int	x;

	y = 1;
	while (y <= size_y)
	{
		x = -1;
		while (++x < size_x)
		{
			ft_putnbr_fd(map[size_y - y][x], 1);
			ft_putstr_fd(" ", 1);
		}
		ft_putstr_fd("\n", 1);
		y++;
	}
}

void	free_fdf_map(t_fdf_map *map)
{
	int	i;

	i = -1;
	if (!map)
		return ;
	if (map->gradient)
		free (map->gradient);
	if (map->map)
	{
		while (++i < map->size_y)
			free (map->map[i]);
		free (map->map);
	}
	free (map);
}

int32_t	main(int argc, char *argv[])
{
	t_fdf_map	*map;
	mlx_t		*mlx;
	mlx_image_t	*img;

	if (argc != 2)
		handle_error("Only 2 arguments are expected.");
	map = init_map(argv[1]);
	mlx = mlx_init(WIDTH, HEIGHT, "FdF", true);
	if (!mlx)
		handle_error("MLX failed.");
	img = mlx_new_image(mlx, WIDTH, HEIGHT);
	if (!img)
	{
		mlx_close_window(mlx);
		handle_error("MLX failed.");
	}
	draw_map(map, img);
	mlx_image_to_window(mlx, img, 0, 0);
	mlx_loop_hook(mlx, ft_hook, mlx);
	mlx_loop(mlx);
	mlx_terminate(mlx);
	free_fdf_map(map);
	return (EXIT_SUCCESS);
}
