/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filler.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchen <cchen@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 10:01:17 by cchen             #+#    #+#             */
/*   Updated: 2022/05/06 16:36:06 by cchen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILLER_H
# define FILLER_H

# define ERROR 0
# define OK 1
# define STDIN 0
/* DELETE ME */
# include <stdio.h>
/* END DELETE ME */

# include "libft.h"

typedef struct s_dimension
{
	int	w;
	int	h;
}				t_dimension;

typedef struct s_map
{
	char		**map;
	char		me;
	char		enemy;
	t_dimension	dimension;
}				t_map;

typedef struct s_piece
{
	char		**pc;
	t_dimension	dimension;
}				t_piece;

int		init(t_map *map);
int		read_map(t_map *map);
int		error(char **array, char *msg);
int		get_dimensions(t_dimension *dimension, char *name);

#endif
