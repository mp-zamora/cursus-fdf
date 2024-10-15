/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpenas-z <mpenas-z@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 17:46:27 by mpenas-z          #+#    #+#             */
/*   Updated: 2024/10/15 18:35:13 by mpenas-z         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

uint32_t	get_color(float x, float y, t_coords o, t_coords d, t_fdf_map *m)
{
	int		color_a[3];
	int		color_b[3];
	int		color_p[3];
	float	percent;

	percent = get_percent(x, y, o, d, m);
	color_a[0] = get_r(COLOR_A);
	color_a[1] = get_g(COLOR_A);
	color_a[2] = get_b(COLOR_A);
	color_b[0] = get_r(COLOR_B);
	color_b[1] = get_g(COLOR_B);
	color_b[2] = get_b(COLOR_B);
	color_p[0] = (color_b[0] * percent) + (color_a[0] * (1 - percent));
	color_p[1] = (color_b[1] * percent) + (color_a[1] * (1 - percent));
	color_p[2] = (color_b[2] * percent) + (color_a[2] * (1 - percent));
	return ((color_p[0] << 24 | color_p[1] << 16 | color_p[2] << 8 | (0xFF)) & 0xFFFFFFFF);
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
