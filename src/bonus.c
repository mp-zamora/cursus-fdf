/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpenas-z <mpenas-z@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 12:56:56 by mpenas-z          #+#    #+#             */
/*   Updated: 2024/10/19 13:36:07 by mpenas-z         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

void	add_zoom(float zoom, t_fdf_map **map)
{
	int	i;
	int	j;

	i = -1;
	(*map)->map = parse_map(open_file((*map)->file), \
					(*map)->size_x, (*map)->size_y);
	(*map)->zoom = zoom;
	while (++i < (*map)->size_y)
	{
		j = -1;
		while (++j < (*map)->size_x)
		{
			(*map)->map[i][j].iso_x *= zoom;
			(*map)->map[i][j].iso_y *= zoom;
		}
	}
	ft_putstr_fd("Zoom added!\n", 1);
}
