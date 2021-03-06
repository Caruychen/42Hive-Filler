/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filler.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchen <cchen@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 10:01:17 by cchen             #+#    #+#             */
/*   Updated: 2022/05/12 19:37:39 by cchen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILLER_H
# define FILLER_H

# define ERROR 0
# define FAIL 0
# define OK 1
# define STDIN 0
# define END 0

# include "libft.h"

typedef struct s_coord
{
	int	row;
	int	col;
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
	t_coord		me_start;
	t_coord		me_end;
}				t_board;

typedef struct s_piece
{
	t_grid			grid;
	t_coord			start;
	t_coord			end;
	t_dimensions	size;
}				t_piece;

int				init(t_board *board, t_piece *piece);
int				read_board(t_board *board);
int				read_piece(t_piece *piece);
int				error(char **array, char *msg);
void			cleanup(t_board board, t_piece piece);
int				skip_line(void);
int				make_grid(t_grid *grid);
int				set_grid(t_grid *grid, int start, char *sample);
int				set_dimensions(t_dimensions *dimensions, char *name);
int				set_heat(t_board *board);
int				init_queue(t_grid heat, t_vec *adj);
int				scan_queue(t_grid *heat, t_vec *adj);
int				place_piece(t_board board, t_piece piece, t_coord *res);
t_dimensions	set_limit(t_board board, t_piece piece);
t_coord			set_start(t_board *board, t_piece piece);
int				is_overlap(char c, t_board board, t_coord b_index,
					t_coord p_index);
int				get_heat(char **array, t_coord b_index, t_coord p_index);

#endif
