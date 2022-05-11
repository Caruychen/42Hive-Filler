/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   play_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchen <cchen@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 14:06:03 by cchen             #+#    #+#             */
/*   Updated: 2022/05/11 14:08:27 by cchen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

t_dimensions	set_limit(t_board board, t_piece piece)
{
	t_dimensions	limit;
	t_dimensions	res;

	limit = board.grid.dimensions;
	if (board.me_end.row < limit.h - piece.size.h - piece.start.row)
		res.h = board.me_end.row + 1;
	else
		res.h = limit.h - piece.size.h - piece.start.row + 1;
	if (board.me_end.col < limit.w - piece.size.w - piece.start.col)
		res.w = board.me_end.col + 1;
	else
		res.w = limit.w - piece.size.w - piece.start.col + 1;
	return (res);
}

t_coord	set_start(t_board *board, t_piece piece)
{
	board->me_start.row = board->me_start.row - piece.end.row;
	if (board->me_start.row + piece.start.row < 0)
		board->me_start.row = 0 - piece.start.row;
	board->me_start.col = board->me_start.col - piece.end.col;
	if (board->me_start.col + piece.start.col < 0)
		board->me_start.col = 0 - piece.start.col;
	return (board->me_start);
}

int	is_overlap(char c, t_board board, t_coord b_index, t_coord p_index)
{
	char	spot;

	spot = board.grid.array[b_index.row + p_index.row]
	[b_index.col + p_index.col];
	return (ft_toupper(spot) == c);
}

int	get_heat(char **array, t_coord b_index, t_coord p_index)
{
	return ((int)(array[b_index.row + p_index.row][b_index.col + p_index.col]));
}
