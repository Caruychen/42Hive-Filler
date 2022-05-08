/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchen <cchen@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 10:00:00 by cchen             #+#    #+#             */
/*   Updated: 2022/05/08 10:03:47 by cchen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

void debug(t_grid grid)
{
	int row = 0;
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
			return (0);
		debug(board.grid);
		debug(piece.grid);
		ft_printf("0 0");
	}
	return (0);
}
