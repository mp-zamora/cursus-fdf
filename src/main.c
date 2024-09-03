/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpenas-z <mpenas-z@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 14:27:02 by mpenas-z          #+#    #+#             */
/*   Updated: 2024/09/03 14:49:54 by mpenas-z         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

int	main(int argc, char *argv[])
{
	/* First we parse the map to: */
	/*	- Extract size && xyz coordinates of every point. */
	// Parsing and extraction:
	//	1. Open file given in args.
	//	2. get_next_line and ft_split result.
	//	3. For every value, record in a lineal array its x, y and z coordinates.
	/* Then we run MLX and create a graphical representation of said array. */
	ft_putstr_fd("This is a test\n", 1);
	/* Finally we free everything when the user exits the GUI. */
	return (0);
}
