/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpenas-z <mpenas-z@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 17:46:27 by mpenas-z          #+#    #+#             */
/*   Updated: 2024/10/20 10:15:55 by mpenas-z         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

#include <stdlib.h>

uint32_t	get_color(float coords[2], t_coords o, t_coords d, t_fdf_map *m)
{
	int		color_a[3];
	int		color_b[3];
	int		color_p[3];
	float	percent;

	percent = get_percent(coords, o, d, m);
	color_a[0] = get_r(m->palette[m->current_palette][0]);
	color_a[1] = get_g(m->palette[m->current_palette][0]);
	color_a[2] = get_b(m->palette[m->current_palette][0]);
	color_b[0] = get_r(m->palette[m->current_palette][1]);
	color_b[1] = get_g(m->palette[m->current_palette][1]);
	color_b[2] = get_b(m->palette[m->current_palette][1]);
	color_p[0] = (color_b[0] * percent) + (color_a[0] * (1 - percent));
	color_p[1] = (color_b[1] * percent) + (color_a[1] * (1 - percent));
	color_p[2] = (color_b[2] * percent) + (color_a[2] * (1 - percent));
	return ((color_p[0] << 24 | color_p[1] << 16 | color_p[2] << 8 | (0xFF)));
}

int	get_r(int rgba)
{
	return ((rgba >> 16) & 0xFF);
}

int	get_g(int rgba)
{
	return ((rgba >> 8) & 0xFF);
}

int	get_b(int rgba)
{
	return ((rgba) & 0xFF);
}

uint32_t	**create_palette(void)
{
	uint32_t	**palette;
	int			i;

	palette = (uint32_t **)malloc(sizeof(uint32_t *) * 5);
	if (!palette)
		handle_error("Malloc failed.");
	i = -1;
	while (++i < 5)
	{
		palette[i] = (uint32_t *)malloc(sizeof(uint32_t) * 2);
		if (!palette[i])
			handle_error("Malloc failed.");
	}
	palette[0][0] = 0x00008B;
	palette[0][0] = 0x7DF9FF;
	palette[1][0] = 0x228B22;
	palette[1][1] = 0xADFF2F;
	palette[2][0] = 0xDC143C;
	palette[2][1] = 0xFFA500;
	palette[3][0] = 0x4B0082;
	palette[3][1] = 0xE6E6FA;
	palette[4][0] = 0xC1440E;
	palette[4][1] = 0xD69A6D;
	return (palette);
}
