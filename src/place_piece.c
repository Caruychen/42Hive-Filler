/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   place_piece.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchen <cchen@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 21:55:37 by cchen             #+#    #+#             */
/*   Updated: 2022/05/11 00:20:31 by cchen            ###   ########.fr       */
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
	t_coord	p_index;
	t_dimensions	limit;
	int		overlaps;
	int		sum;

	p_index = piece.start;
	limit.h = piece.start.row + piece.real_size.h;
	limit.w = piece.start.col + piece.real_size.w;
	sum = 0;
	overlaps = 0;
	while (p_index.row < limit.h)
	{
		while (p_index.col < limit.w)
		{
			if (piece.grid.array[p_index.row][p_index.col] == '*')
			{
				if (is_overlap(board.enemy, board, b_index, p_index))
					return (-1);
				if (is_overlap(board.me, board, b_index, p_index))
					overlaps++;
				if (overlaps > 1)
					return (-1);
				sum += get_heat(board.heat.array, b_index, p_index);
			}
			p_index.col++;
		}
		p_index.row++;
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
	res.h = board.start.row + board.real_size.h;
	if (res.h > limit.h - piece.real_size.h + 1)
		res.h = limit.h - piece.real_size.h + 1;
	res.w = board.start.col + board.real_size.w;
	if (res.w > limit.w - piece.real_size.w + 1)
		res.w = limit.w - piece.real_size.w + 1;
	return (res);
}

static t_coord	set_start(t_board *board, t_piece piece)
{
	board->start.row = board->start.row - (piece.start.row + piece.real_size.h) + 1;
	if (piece.start.row + board->start.row < 0)
		board->start.row = 0 - piece.start.row;
	board->start.col = board->start.col - (piece.start.col + piece.real_size.w) + 1;
	if (piece.start.col + board->start.col < 0)
		board->start.col = 0 - piece.start.col;
	return (board->start);
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
		index.col = board.start.col;
		while (index.col < limit.w)
		{
			heat = check_piece(board, piece, index);
			if (heat != -1 && (heat < min || min == -1))
			{
				min = heat;
				res->row = index.row - piece.start.row;
				res->col = index.col - piece.start.col;
			}
			index.col++;
		}
		index.row++;
	}
	return (OK);
}
