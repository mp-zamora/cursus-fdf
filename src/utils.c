/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpenas-z <mpenas-z@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 18:48:38 by mpenas-z          #+#    #+#             */
/*   Updated: 2024/09/28 16:28:45 by mpenas-z         ###   ########.fr       */
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
