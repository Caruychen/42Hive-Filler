/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_piece.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchen <cchen@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/06 17:12:31 by cchen             #+#    #+#             */
/*   Updated: 2022/05/11 00:23:07 by cchen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

static int	make_piece(t_piece *piece)
{
	if (piece->grid.array)
		ft_strdelarray(&(piece->grid.array));
	if (!set_dimensions(&(piece->grid.dimensions), "Piece"))
		return (error(NULL, "Error reading dimensions: make_piece()"));
	return (make_grid(&(piece->grid)));
}

static void	update_piece(t_piece *piece, t_coord coord)
{
	if (coord.row < piece->start.row)
		piece->start.row = coord.row;
	if (coord.row > piece->end.row)
		piece->end.row = coord.row;
	if (coord.col < piece->start.col)
		piece->start.col = coord.col;
	if (coord.col > piece->end.col)
		piece->end.col = coord.col;
}

static int	seek_piece(t_piece *piece)
{
	t_coord			coord;
	t_dimensions	limit;
	char			**array;

	array = piece->grid.array;
	limit = piece->grid.dimensions;
	piece->start = (t_coord){.row = limit.h, .col = limit.w};
	coord.row = 0;
	while (coord.row < limit.h)
	{
		coord.col = 0;
		while (coord.col < limit.w)
		{
			if (array[coord.row][coord.col] == '*')
				update_piece(piece, coord);
			coord.col++;
		}
		coord.row++;
	}
	return (OK);
}

int	read_piece(t_piece *piece)
{
	if (!make_piece(piece))
		return (error(NULL, "Error making piece: read_piece()"));
	if (!set_grid(&(piece->grid), 0, ".*"))
		return (error(NULL, "Failed to set grid: read_piece()"));
	return (seek_piece(piece));
}
