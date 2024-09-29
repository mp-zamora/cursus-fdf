/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpenas-z <mpenas-z@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 18:48:38 by mpenas-z          #+#    #+#             */
/*   Updated: 2024/09/29 18:07:31 by mpenas-z         ###   ########.fr       */
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
	return (isometric_map);
}
