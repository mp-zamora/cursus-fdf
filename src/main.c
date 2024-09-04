/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpenas-z <mpenas-z@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 14:27:02 by mpenas-z          #+#    #+#             */
/*   Updated: 2024/09/04 15:50:09 by mpenas-z         ###   ########.fr       */
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
	
	y = 0;
	while (y < size_y)
	{
		x = -1;
		while (++x < size_x)
		{
			ft_putnbr_fd(map[y][x], 1);
			ft_putstr_fd(" ", 1);
		}
		ft_putstr_fd("\n", 1);
		y++;
	}
}

int	main(int argc, char *argv[])
{
	int	**map;
	int	size_x;
	int	size_y;

	if (argc != 2)
		handle_error();
	size_x = get_max_x(open_file(argv[1]));
	size_y = get_max_y(open_file(argv[1]));
	map = parse_map(open_file(argv[1]), size_x, size_y);
	if (map == NULL)
		handle_error();
	/* Then we run MLX and create a graphical representation of said array. */
	// print_map(map, size_x, size_y);
	/* Finally we free everything when the user exits the GUI. */
	return (0);
}
