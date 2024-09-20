/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpenas-z <mpenas-z@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 18:48:38 by mpenas-z          #+#    #+#             */
/*   Updated: 2024/09/20 18:49:00 by mpenas-z         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

void	fill_gradient(int **gradient)
{
	int	i;

	if (!(*gradient))
		return ;
	i = -1;
	while (++i < 256)
		(*gradient)[i] = i;
}
