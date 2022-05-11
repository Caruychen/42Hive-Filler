/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchen <cchen@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 10:00:00 by cchen             #+#    #+#             */
/*   Updated: 2022/05/11 14:00:03 by cchen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

int	main(void)
{
	t_board	board;
	t_piece	piece;
	t_coord	res;

	if (!init(&board, &piece))
		return (0);
	while (1)
	{
		if (read_board(&board) != OK)
			return (0);
		if (!read_piece(&piece))
			return (error(board.grid.array, "Error: read piece failed"));
		if (!set_heat(&board))
			return (error(piece.grid.array, "Error: set heat map failed"));
		if (place_piece(board, piece, &res))
			ft_printf("%d %d\n", res.row, res.col);
		else
			break ;
	}
	cleanup(board, piece);
	ft_printf("0 0\n");
	return (END);
}
