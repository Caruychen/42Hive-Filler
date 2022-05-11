/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   place_piece.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchen <cchen@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 21:55:37 by cchen             #+#    #+#             */
/*   Updated: 2022/05/11 14:42:14 by cchen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

static int	is_valid_spot(t_board board, t_piece piece, t_coord b_index,
		int *overlaps)
{
	if (is_overlap(board.enemy, board, b_index, piece.start))
		return (0);
	if (is_overlap(board.me, board, b_index, piece.start) && ++(*overlaps) > 1)
		return (0);
	return (OK);
}

static int	check_piece(t_board board, t_piece piece, t_coord b_index)
{
	int		overlaps;
	int		sum;
	int		reset_col;

	sum = 0;
	overlaps = 0;
	reset_col = piece.start.col;
	while (piece.start.row < piece.end.row + 1)
	{
		piece.start.col = reset_col;
		while (piece.start.col < piece.end.col + 1)
		{
			if (piece.grid.array[piece.start.row][piece.start.col] == '*')
			{
				if (!is_valid_spot(board, piece, b_index, &overlaps))
					return (-1);
				sum += get_heat(board.heat.array, b_index, piece.start);
			}
			piece.start.col++;
		}
		piece.start.row++;
	}
	return ((overlaps == 1) * sum - 1);
}

int	place_piece(t_board board, t_piece piece, t_coord *res)
{
	t_dimensions	limit;
	t_coord			index;
	int				min;
	int				heat;

	limit = set_limit(board, piece);
	index = set_start(&board, piece);
	min = -1;
	while (index.row < limit.h)
	{
		index.col = board.me_start.col;
		while (index.col < limit.w)
		{
			heat = check_piece(board, piece, index);
			if (heat != -1 && (heat < min || min == -1))
			{
				min = heat;
				*res = index;
			}
			index.col++;
		}
		index.row++;
	}
	return (!(min == -1));
}
