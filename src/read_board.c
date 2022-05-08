/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_board.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchen <cchen@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 13:10:11 by cchen             #+#    #+#             */
/*   Updated: 2022/05/08 11:39:24 by cchen            ###   ########.fr       */
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

int read_board(t_board *board)
{
	if (!make_board(board))
		return (error(NULL, "Error making board: read_board()"));
	skip_line();
	return (set_grid(&(board->grid), 4, ".oOxX"));
}
