/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpenas-z <mpenas-z@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 17:50:11 by mpenas-z          #+#    #+#             */
/*   Updated: 2024/11/09 17:51:17 by mpenas-z         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

void	close_hook(void *param)
{
	t_fdf_map	*map;

	map = param;
	if (mlx_is_key_down(map->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(map->mlx);
}

void	key_hook(mlx_key_data_t keydata, void *param)
{
	t_fdf_map	**map;

	map = param;
	if (keydata.key == MLX_KEY_SPACE && keydata.action == MLX_PRESS)
	{
		if ((*map)->current_palette < 4)
			(*map)->current_palette++;
		else
			(*map)->current_palette = 0;
		(*map)->img = render_map((*map));
	}
}
