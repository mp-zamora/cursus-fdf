/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpenas-z <mpenas-z@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 18:48:38 by mpenas-z          #+#    #+#             */
/*   Updated: 2024/10/01 20:46:39 by archangelus      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

int	*fill_gradient(void)
{
	int	i;
	int	*gradient;

	gradient = (int *)malloc(sizeof(int) * 256);
	if (!gradient)
		return (NULL);
	i = -1;
	while (++i < 256)
		gradient[i] = i;
	return (gradient);
}

/* WARNING WIP: isometric_map contains both matrices: x in index 0, and y in index 1 */
int	**convert_to_iso(int **map, int size_x, int size_y)
{
	int	**isometric_map;
	int	i;
	int	j;
	int	k;

	isometric_map = (int **)malloc(sizeof(int *) * 2);
	if (!isometric_map)
		handle_error("Isometric map malloc failed.");
	isometric_map[0] = (int *)malloc(sizeof(int) * size_x * size_y);
	isometric_map[1] = (int *)malloc(sizeof(int) * size_x * size_y);
	if (!isometric_map[0] || !isometric_map[1])
		handle_error("Isometric map submallocs failed.");
	k = 0;
	i = -1;
	while (++i < size_y)
	{
		j = -1;
		while (++j < size_x)
		{
			isometric_map[0][k] = j * cos(0.785398) + i * cos(2.785398) + map[i][j] * cos(-1.214602);
			isometric_map[1][k] = j * sin(0.785398) + i * sin(2.785398) + map[i][j] * sin(-1.214602);
			k++;
		}
	}
	ft_putstr_fd("Before correcting offset...\n", 1);
	return(correct_offset(isometric_map, size_x * size_y));
}

int	**correct_offset(int **isometric, int total_size)
{
	int	i;
	int	x_offset;
	int	y_offset;
	int	**isometric_map;

	i = -1;
	x_offset = 0;
	y_offset = 0;
	isometric_map = (int **)malloc(sizeof(int *) * 2);
	if (!isometric_map)
		handle_error("Isometric map malloc failed.");
	isometric_map[0] = (int *)malloc(sizeof(int) * total_size);
	isometric_map[1] = (int *)malloc(sizeof(int) * total_size);
	if (!isometric_map[0] || !isometric_map[1])
		handle_error("Isometric map submallocs failed.");
	while (++i < total_size)
	{
		if (isometric[0][i] < 0 && abs(isometric[0][i]) > x_offset)
			x_offset = abs(isometric[0][i]) + 1;
		if (isometric[1][i] < 0 && abs(isometric[1][i]) > y_offset)
			y_offset = abs(isometric[1][i]) + 1;
	}
	ft_putstr_fd("Before adding offset...\n", 1);
	i = -1;
	while (++i < total_size)
	{
		isometric_map[0][i] = isometric[0][i] + x_offset;
		isometric_map[1][i] = isometric[1][i] + y_offset;
	}
	free (isometric[0]);
	free (isometric[1]);
	free (isometric);
	ft_putstr_fd("Offset added!\n", 1);
	return (isometric_map);
}
