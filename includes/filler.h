/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filler.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchen <cchen@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 10:01:17 by cchen             #+#    #+#             */
/*   Updated: 2022/05/09 11:17:42 by cchen            ###   ########.fr       */
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

typedef struct s_coord
{
	int	row;
	int col;
}				t_coord;

typedef struct s_dimensions
{
	int	w;
	int	h;
}				t_dimensions;

typedef struct s_grid
{
	char			**array;
	t_dimensions	dimensions;
}				t_grid;

typedef struct s_board
{
	t_grid		grid;
	t_grid		heat;
	char		me;
	char		enemy;
}				t_board;

typedef struct s_piece
{
	t_grid		grid;
}				t_piece;

int		init(t_board *board, t_piece *piece);
int		read_board(t_board *board);
int		read_piece(t_piece *piece);
int		error(char **array, char *msg);
int		skip_line(void);
int		make_grid(t_grid *grid);
int		is_valid_line(char *line, int width, char *sample);
int		set_grid(t_grid *grid, int start, char *sample);
int		set_dimensions(t_dimensions *dimensions, char *name);
int		set_heat(t_board *board);

#endif
