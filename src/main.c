/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpenas-z <mpenas-z@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 14:27:02 by mpenas-z          #+#    #+#             */
/*   Updated: 2024/09/03 15:21:48 by mpenas-z         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

/* I'll use lists to store the coordinates of every spatial point */
t_point	*parse_map(int argc, char *argv[])
{
	t_point	*points;
	char	*buffer;
	int		total_points;

	// Check if args are OK
	if (argc != 2)
		return (0);
	total_points = 0;
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
	{
		perror("Error opening file");
		close (fd);
		return (0);
	}
	/* Fill the list with points */
	buffer = get_next_line(fd);
	while (buffer != NULL)
	{
		// ft_split buffer, create new node for each element.
		// Do function that reads string, and creates struct.
		buffer = get_next_line(fd);
	}
	close(fd);
	return (1);
}

int	main(int argc, char *argv[])
{
	/* First we parse the map to: */
	/*	- Extract size && xyz coordinates of every point. */
	// Parsing and extraction:
	//	1. Open file given in args.
	//	2. get_next_line and ft_split result.
	//	3. For every value, record in a lineal array its x, y and z coordinates.
	parse_map(argc, argv);
	/* Then we run MLX and create a graphical representation of said array. */
	ft_putstr_fd("This is a test\n", 1);
	/* Finally we free everything when the user exits the GUI. */
	return (0);
}
