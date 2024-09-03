/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpenas-z <mpenas-z@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 14:31:22 by mpenas-z          #+#    #+#             */
/*   Updated: 2024/09/03 15:22:25 by mpenas-z         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H
# include "../libft/libft.h"
# include <stdlib.h>
# include <stdio.h>
# include <limits.h>
# include <math.h>

typedef	struct	s_point
{
	int	x;
	int	z;
	int	y;
	t_point	*next;
	t_point	*prev;
}	t_point;

t_point	*parse_map(int argc, char *argv[]);

#endif
