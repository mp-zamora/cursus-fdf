/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpenas-z <mpenas-z@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 11:38:49 by mpenas-z          #+#    #+#             */
/*   Updated: 2024/09/04 13:33:55 by mpenas-z         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

int	get_max_x(int fd)
{
	char	*buffer;
	
	buffer = get_next_line(fd);
	if (!buffer)
		return (0);
	close (fd);
	return (ft_countwords(buffer, ' '));
}

int	get_max_y(int fd)
{
	char	*buffer;
	int		y;

	y = 0;
	buffer = get_next_line(fd);
	while (buffer)
	{
		y++;
		buffer = get_next_line(fd);
	}
	close (fd);
	return (y);	
}

int	**parse_map(int fd, int size_x, int size_y)
{
	int		**map;
	char	*buffer;
	char	**aux_buffers;
	int		x;
	int		y;

	map = (int **)malloc(sizeof(int *) * size_y);
	buffer = get_next_line(fd);
	y = 0;
	while (buffer != NULL)
	{
		aux_buffers = ft_split(buffer, ' ');
		x = -1;
		while (++x < size_x)
		{
			map[y] = (int *)malloc(sizeof(int) * size_x);
			map[y][x] = ft_atoi(aux_buffers[x]);
			/*ft_putnbr_fd(map[y][x], 1);*/
			/*ft_putstr_fd(" ", 1);*/
		}
		/*ft_putstr_fd("\n", 1);*/
		buffer = get_next_line(fd);
		y++;
	}
	close(fd);
	print_map(map, size_x, size_y);
	return (map);
}
