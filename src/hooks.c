/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpenas-z <mpenas-z@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 17:41:44 by mpenas-z          #+#    #+#             */
/*   Updated: 2024/11/09 17:45:09 by mpenas-z         ###   ########.fr       */
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

void	handle_zoom_rotation_key(mlx_key_data_t keydata, t_fdf_map **map)
{
	if (keydata.key == MLX_KEY_Z && keydata.action == MLX_PRESS)
		(*map)->img = add_zoom((*map)->zoom * 1.1, map);
	if (keydata.key == MLX_KEY_X && keydata.action == MLX_PRESS)
		(*map)->img = add_zoom((*map)->zoom * 0.9, map);
	if (keydata.key == MLX_KEY_Q && keydata.action == MLX_PRESS)
		(*map)->img = add_rotation(0.3, map);
	if (keydata.key == MLX_KEY_E && keydata.action == MLX_PRESS)
		(*map)->img = add_rotation(-0.3, map);
}

void	handle_translation_key(mlx_key_data_t keydata, t_fdf_map **map)
{
	if (keydata.key == MLX_KEY_A && keydata.action == MLX_PRESS)
		(*map)->img = add_translation(0.1, 0, map);
	if (keydata.key == MLX_KEY_D && keydata.action == MLX_PRESS)
		(*map)->img = add_translation(-0.1, 0, map);
	if (keydata.key == MLX_KEY_W && keydata.action == MLX_PRESS)
		(*map)->img = add_translation(0, 0.1, map);
	if (keydata.key == MLX_KEY_S && keydata.action == MLX_PRESS)
		(*map)->img = add_translation(0, -0.1, map);
}

void	handle_projection_key(mlx_key_data_t keydata, t_fdf_map **map)
{
	if (keydata.key == MLX_KEY_R && keydata.action == MLX_PRESS)
		(*map)->img = perspective_projection(0, map);
	if (keydata.key == MLX_KEY_T && keydata.action == MLX_PRESS)
		(*map)->img = perspective_projection(1, map);
	if (keydata.key == MLX_KEY_Y && keydata.action == MLX_PRESS)
		(*map)->img = perspective_projection(2, map);
	if (keydata.key == MLX_KEY_U && keydata.action == MLX_PRESS)
		(*map)->img = perspective_projection(3, map);
}

void	bonus_hook(mlx_key_data_t keydata, void *param)
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
	handle_zoom_rotation_key(keydata, map);
	handle_translation_key(keydata, map);
	handle_projection_key(keydata, map);
}
