/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpenas-z <mpenas-z@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 17:46:27 by mpenas-z          #+#    #+#             */
/*   Updated: 2024/10/11 00:12:47 by archangelus      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"
// REMOVE BELOW
#include <stdio.h>
// REMOVE ABOVE


// The idea is to get the colors of o and d, then calculate the relative
// % of x and y, and then get the color of that point.
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
	printf("COLORA: %#08x\n", (color_a[0] << 16 | color_a[1] << 8 | color_a[2]));
	color_b[0] = get_r(COLOR_B);
	color_b[1] = get_g(COLOR_B);
	color_b[2] = get_b(COLOR_B);
	printf("COLORB: %#08x\n", (color_b[0] << 16 | color_b[1] << 8 | color_b[2]));
	color_p[0] = (color_b[0] - color_a[0]) * percent;
	color_p[1] = (color_b[1] - color_a[1]) * percent;
	color_p[2] = (color_b[2] - color_a[2]) * percent;
	/* WARNING remove printf*/
	printf("COLOR: %#08x\n", ((color_p[0] << 24 | color_p[1] << 16 | color_p[2] << 8 | (0xFF)) & 0xFFFFFFFF));
	// REMOVE ABOVE
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

/*int get_a(int rgba)*/
/*{*/
/*    return (rgba & 0xFF);*/
/*}*/
