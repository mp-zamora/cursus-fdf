/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpenas-z <mpenas-z@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 18:48:38 by mpenas-z          #+#    #+#             */
/*   Updated: 2024/10/03 18:31:23 by archangelus      ###   ########.fr       */
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

float	*get_max_coords(t_coords **map, int size_x, int size_y)
{
	int		i;
	int		j;
	float	*max_coords;

	i = 0;
	max_coords = (float *)malloc(sizeof(float) * 2);
	if (!max_coords)
		handle_error("max_coords malloc faile.");
	max_coords[0] = 0;
	max_coords[1] = 0;
	while (i < size_y)
	{
		j = 0;
		while (j < size_x)
		{
			if (map[i][j].iso_x > max_coords[0])
				max_coords[0] = map[i][j].iso_x;
			if (map[i][j].iso_y > max_coords[1])
				max_coords[1] = map[i][j].iso_y;
			j++;
		}
		i++;
	}
	return (max_coords);
}
