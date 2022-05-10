/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchen <cchen@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 10:00:00 by cchen             #+#    #+#             */
/*   Updated: 2022/05/10 23:24:48 by cchen            ###   ########.fr       */
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
		if (!read_board(&board))
			return (0);
		if (!read_piece(&piece))
			return (error(board.grid.array, "Error: read piece failed"));
		if (!set_heat(&board))
			return (error(piece.grid.array, "Error: set heat map failed"));
		if (place_piece(board, piece, &res))
			ft_printf("%d %d\n", res.col, res.row);
		else
		{
			ft_strdelarray(&board.grid.array);
			ft_strdelarray(&board.heat.array);
			ft_strdelarray(&piece.grid.array);
			return (0);
		}
	}
	return (0);
}
