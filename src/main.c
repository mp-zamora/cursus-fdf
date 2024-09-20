/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpenas-z <mpenas-z@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 14:27:02 by mpenas-z          #+#    #+#             */
/*   Updated: 2024/09/20 13:25:33 by mpenas-z         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

void	handle_error(void)
{
	ft_putstr_fd("Error\n", 2);
	exit(2);
}

int	open_file(char *file)
{
	int	fd;

	fd = open(file, O_RDONLY);
	if (fd == -1)
		handle_error();
	return (fd);
}

void	print_map(int **map, int size_y, int size_x)
{
	int	y;
	int x;
	
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

void	free_fdf_map(int **map, int size)
{
	int	i;

	i = -1;
	if (!map)
		return ;
	while (++i < size)
		free (map[i]);
	free (map);
}

int32_t	main(int argc, char *argv[])
{
	int	**map;
	int	size_x;
	int	size_y;
	mlx_t* mlx;
	mlx_image_t* img;

	if (argc != 2)
		handle_error();
	mlx = mlx_init(WIDTH, HEIGHT, "FdF", true);
	if (!mlx)
		handle_error();
	img = mlx_new_image(mlx, WIDTH, HEIGHT);
	if (!img || (mlx_image_to_window(mlx, img, 0, 0) < 0))
	{
		mlx_close_window(mlx);
		handle_error();
	}
	size_x = get_max_x(open_file(argv[1]));
	size_y = get_max_y(open_file(argv[1]));
	map = parse_map(open_file(argv[1]), size_x, size_y);
	if (map == NULL)
		handle_error();
	else
		print_map(map, size_y, size_x);
	mlx_loop_hook(mlx, ft_hook, mlx);
	mlx_loop(mlx);
	mlx_terminate(mlx);
	free_fdf_map(map, size_y);
	return (EXIT_SUCCESS);
}
