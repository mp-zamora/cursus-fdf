/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpenas-z <mpenas-z@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 14:27:02 by mpenas-z          #+#    #+#             */
/*   Updated: 2024/11/09 18:05:31 by mpenas-z         ###   ########.fr       */
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

void	free_fdf_map(t_fdf_map *map)
{
	if (!map)
		return ;
	if (map->max_coords)
		free (map->max_coords);
	if (map->translation)
		free (map->translation);
	free_fdf_map_arrays(map);
	free (map);
}

void	free_fdf_map_arrays(t_fdf_map *map)
{
	int	i;

	if (map->palette)
	{
		i = -1;
		while (++i < 5)
			free (map->palette[i]);
		free (map->palette);
	}
	if (map->map)
	{
		i = -1;
		while (++i < map->size_y)
			free (map->map[i]);
		free (map->map);
	}
	if (map->original)
	{
		i = -1;
		while (++i < map->size_y)
			free (map->original[i]);
		free (map->original);
	}
}

int32_t	main(int argc, char *argv[])
{
	t_fdf_map	*map;

	if (argc != 2)
		handle_error("Only 2 arguments are expected.");
	map = init_map(argv[1]);
	map->img = NULL;
	map->mlx = mlx_init(WIDTH, HEIGHT, "FdF", true);
	if (!(map->mlx))
		handle_error("MLX failed.");
	center_map(&map);
	map->img = render_map(map);
	mlx_loop_hook(map->mlx, close_hook, map);
	mlx_key_hook(map->mlx, &key_hook, &map);
	mlx_loop(map->mlx);
	mlx_terminate(map->mlx);
	free_fdf_map(map);
	return (EXIT_SUCCESS);
}
