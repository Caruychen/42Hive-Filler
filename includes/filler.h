/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filler.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchen <cchen@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 10:01:17 by cchen             #+#    #+#             */
/*   Updated: 2022/05/05 16:05:01 by cchen            ###   ########.fr       */
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

typedef struct s_map
{
	char	**map;
	char	me;
	char	enemy;
	int		width;
	int		height;
}				t_map;

typedef struct s_piece
{
	char	**pc;
	int		width;
	int		height;
}				t_piece;

void	init(t_map *map);
int		init_map(t_map *map);
int		error(t_map *map, char *msg);

#endif
