/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpenas-z <mpenas-z@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 18:48:38 by mpenas-z          #+#    #+#             */
/*   Updated: 2024/10/03 13:43:02 by mpenas-z         ###   ########.fr       */
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
float	**convert_to_iso(int **map, int size_x, int size_y, float alpha)
{
	float	**isometric_map;
	int	i;
	int	j;
	int	k;

	isometric_map = (float **)malloc(sizeof(float *) * 2);
	if (!isometric_map)
		handle_error("Isometric map malloc failed.");
	isometric_map[0] = (float *)malloc(sizeof(float) * size_x * size_y);
	isometric_map[1] = (float *)malloc(sizeof(float) * size_x * size_y);
	if (!isometric_map[0] || !isometric_map[1])
		handle_error("Isometric map submallocs failed.");
	k = 0;
	i = -1;
	while (++i < size_y)
	{
		j = -1;
		while (++j < size_x)
		{
			isometric_map[0][k] = j * cosf(alpha) \
				+ i * cosf(alpha + 2) \
				+ map[i][j] * cosf(alpha - 2);
			isometric_map[1][k] = j * sinf(alpha) \
				+ i * sinf(alpha + 2) \
				+ map[i][j] * sinf(alpha - 2);
			isometric_map[0][k] *= 20;
			isometric_map[1][k] *= 20;
			k++;
		}
	}
	ft_putstr_fd("Before correcting offset...\n", 1);
	return(correct_offset(isometric_map, size_x * size_y));
}

float	**correct_offset(float **isometric, int total_size)
{
	int		i;
	float	x_offset;
	float	y_offset;
	float	**isometric_map;

	i = -1;
	x_offset = 0;
	y_offset = 0;
	isometric_map = (float **)malloc(sizeof(float *) * 2);
	if (!isometric_map)
		handle_error("Isometric map malloc failed.");
	isometric_map[0] = (float *)malloc(sizeof(float) * total_size);
	isometric_map[1] = (float *)malloc(sizeof(float) * total_size);
	if (!isometric_map[0] || !isometric_map[1])
		handle_error("Isometric map submallocs failed.");
	while (++i < total_size)
	{
		if (isometric[0][i] < 0 && fabs(isometric[0][i]) > x_offset)
			x_offset = fabs(isometric[0][i]) + 1;
		if (isometric[1][i] < 0 && fabs(isometric[1][i]) > y_offset)
			y_offset = fabs(isometric[1][i]) + 1;
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

float	*get_max_coords(float **isometric, int total_size)
{
	int		i;
	float	*max_coords;

	i = 0;
	max_coords = (float *)malloc(sizeof(float) * 2);
	if (!max_coords)
		handle_error("max_coords malloc faile.");
	max_coords[0] = 0;
	max_coords[1] = 0;
	while (i < total_size)
	{
		if (isometric[0][i] > max_coords[0])
			max_coords[0] = isometric[0][i];
		if (isometric[1][i] > max_coords[1])
			max_coords[1] = isometric[1][i];
		i++;
	}
	return (max_coords);
}
