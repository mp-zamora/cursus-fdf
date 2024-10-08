/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpenas-z <mpenas-z@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 17:46:27 by mpenas-z          #+#    #+#             */
/*   Updated: 2024/10/08 19:34:25 by mpenas-z         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"
// REMOVE BELOW
#include <stdio.h>
// REMOVE ABOVE

uint32_t	get_color(float x, float y, t_coords min, t_coords max)
{
	int		color_a[4];
	int		color_b[4];
	int		color_p[4];
	float	percent;

	percent = get_percent(x, y, min, max);
	color_a[0] = get_r(COLOR_A);
	color_a[1] = get_g(COLOR_A);
	color_a[2] = get_b(COLOR_A);
	color_a[3] = (0xFF << 24);;
	color_b[0] = get_r(COLOR_B);
	color_b[1] = get_g(COLOR_B);
	color_b[2] = get_b(COLOR_B);
	color_b[3] = (0xFF << 24);;
	color_p[0] = (color_a[0] + (color_b[0] - color_a[0]) * percent);
	color_p[1] = (color_a[1] + (color_b[1] - color_a[1]) * percent);
	color_p[2] = (color_a[2] + (color_b[2] - color_a[2]) * percent);
	color_p[3] = (0xFF);
	/* WARNING remove printf*/
	printf("A: %#10x\n", color_p[3]);
	printf("COLOR: %#10x\n", (color_p[0] << 24 | color_p[1] << 16 | color_p[2] << 8 | color_p[3]));
	// REMOVE ABOVE
	return (color_p[0] << 24 | color_p[1] << 16 | color_p[2] << 8 | color_p[3]);
}

int	get_r(int rgba)
{
	return ((rgba >> 24) & 0xFF);
}

int	get_g(int rgba)
{
	return ((rgba >> 16) & 0xFF);
}

int	get_b(int rgba)
{
	return ((rgba >> 8) & 0xFF);
}

int get_a(int rgba)
{
    return (rgba & 0xFF);
}
