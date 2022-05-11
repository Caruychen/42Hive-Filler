/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   place_piece.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchen <cchen@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 21:55:37 by cchen             #+#    #+#             */
/*   Updated: 2022/05/11 10:49:18 by cchen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

static int	is_overlap(char c, t_board board, t_coord b_index, t_coord p_index)
{
	char	spot;

	spot = board.grid.array[b_index.row + p_index.row][b_index.col + p_index.col];
	return (ft_toupper(spot) == c);
}

static int	get_heat(char **array, t_coord b_index, t_coord p_index)
{
	return ((int)(array[b_index.row + p_index.row][b_index.col + p_index.col]));
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
				if (is_overlap(board.enemy, board, b_index, piece.start))
					return (-1);
				if (is_overlap(board.me, board, b_index, piece.start))
					overlaps++;
				if (overlaps > 1)
					return (-1);
				sum += get_heat(board.heat.array, b_index, piece.start);
			}
			piece.start.col++;
		}
		piece.start.row++;
	}
	if (overlaps == 0)
		return (-1);
	return (sum);
}

static t_dimensions	set_limit(t_board board, t_piece piece)
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

static t_coord	set_start(t_board *board, t_piece piece)
{
	board->me_start.row = board->me_start.row - piece.end.row;
	if (board->me_start.row + piece.start.row < 0)
		board->me_start.row = 0 - piece.start.row;
	board->me_start.col = board->me_start.col - piece.end.col;
	if (board->me_start.col + piece.start.col < 0)
		board->me_start.col = 0 - piece.start.col;
	return (board->me_start);
}

int	place_piece(t_board board, t_piece piece, t_coord *res)
{
	t_dimensions	limit;
	t_coord		index;
	int		min;
	int		heat;

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
	return (OK);
}
