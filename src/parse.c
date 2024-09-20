/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpenas-z <mpenas-z@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 11:38:49 by mpenas-z          #+#    #+#             */
/*   Updated: 2024/09/20 11:57:52 by mpenas-z         ###   ########.fr       */
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

void	free_buffers(char **buffers, int size)
{
	int	i;

	i = -1;
	if (!buffers)
		return ;
	while (++i < size)
		free (buffers[i]);
	free (buffers);
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
	y = 1;
	while (buffer != NULL)
	{
		ft_putstr_fd("Buffer (y=", 1);
		ft_putnbr_fd(y, 1);
		ft_putstr_fd("): ", 1);
		ft_putstr_fd(buffer, 1);
		aux_buffers = ft_split(buffer, ' ');
		x = -1;
		map[size_y - y] = (int *)malloc(sizeof(int) * size_x);
		while (++x < size_x)
			map[size_y - y][x] = ft_atoi(aux_buffers[x]);
		free_buffers(aux_buffers, size_x);
		buffer = get_next_line(fd);
		y++;
	}
	close(fd);
	return (map);
}
