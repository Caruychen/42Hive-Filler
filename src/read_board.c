/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_board.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchen <cchen@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 13:10:11 by cchen             #+#    #+#             */
/*   Updated: 2022/05/11 10:33:10 by cchen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
* Attempts to Make a new empty board and fills the board using set_grid, which
* reads input line by line into the declared grid.
* The line is skipped twice. First, if the board grid already exists (mid-game)
* then we skip the dimensions line.
* The second skip skips the number line 01234....
*/

#include "filler.h"

static int	make_board(t_board *board)
{
	if (board->grid.array)
		return (skip_line());
	if (!set_dimensions(&(board->grid.dimensions), "Plateau"))
		return (error(NULL, "Error reading dimensions: make_board()"));
	return (make_grid(&(board->grid)));
}

static void	update_board(t_board *board, t_coord coord)
{
	if (coord.row < board->me_start.row)
		board->me_start.row = coord.row;
	if (coord.row > board->me_end.row)
		board->me_end.row = coord.row;
	if (coord.col < board->me_start.col)
		board->me_start.col = coord.col;
	if (coord.col > board->me_end.col)
		board->me_end.col = coord.col;
}

static int	seek_me(t_board *board)
{
	t_coord			coord;
	t_dimensions	limit;
	char			**array;

	array = board->grid.array;
	limit = board->grid.dimensions;
	board->me_start = (t_coord){.row = limit.h, .col = limit.w};
	coord.row = 0;
	while (coord.row < limit.h)
	{
		coord.col = 0;
		while (coord.col < limit.w)
		{
			if (ft_toupper(array[coord.row][coord.col]) == board->me)
				update_board(board, coord);
			coord.col++;
		}
		coord.row++;
	}
	return (OK);
}

int	read_board(t_board *board)
{
	ft_bzero(&(board->me_start), sizeof(board->me_start));
	ft_bzero(&(board->me_end), sizeof(board->me_end));
	if (!make_board(board))
		return (error(NULL, "Error making board: read_board()"));
	skip_line();
	if (!set_grid(&(board->grid), 4, ".oOxX"))
		return (error(NULL, "Error setting grid: read_board()"));
	return (seek_me(board));
}
