/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchen <cchen@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 10:00:00 by cchen             #+#    #+#             */
/*   Updated: 2022/05/10 21:43:54 by cchen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

void	debug(t_grid grid)
{
	int	row;

	row = 0;
	while (row < grid.dimensions.h)
	{
		ft_putendl_fd(grid.array[row], 2);
		row++;
	}
}

int	main(void)
{
	t_board	board;
	t_piece	piece;

	if (!init(&board, &piece))
		return (0);
	while (1)
	{
		if (!read_board(&board))
			return (0);
		if (!read_piece(&piece))
			return (error(board.grid.array, "Error: read piece failed"));
		if (!set_heat(&board))
			return (error(piece.grid.array, "Error: set heat map failed"));
		dprintf(2, "start: %d %d, size: %d %d\n", board.start.row, board.start.col, board.real_size.h, board.real_size.w);
		dprintf(2, "start: %d %d, size: %d %d\n", piece.start.row, piece.start.col, piece.real_size.h, piece.real_size.w);
	/*
		debug(board.grid);
		debug(piece.grid);
	*/
		ft_printf("0 0");
	}
	return (0);
}
