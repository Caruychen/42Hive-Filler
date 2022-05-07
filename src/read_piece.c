/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_piece.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchen <cchen@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/06 17:12:31 by cchen             #+#    #+#             */
/*   Updated: 2022/05/07 16:09:36 by cchen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

static int	make_piece(t_piece *piece)
{
	if (piece->grid.array)
		ft_strdelarray(&(piece->grid.array));
	return (make_array(&(piece->grid), "Piece"));
}

int	read_piece(t_piece *piece)
{
	char	*line;
	int		row;
	int		height;
	int		width;

	if (!make_piece(piece))
		return (error(NULL, "Error making piece: read_piece()"));
	height = piece->grid.dimensions.h;
	width = piece->grid.dimensions.w;
	row = 0;
	while (row < height)
	{
		if (get_next_line(0, &line) <= 0)
			return (error(piece->grid.array, "Error reading input line: read_piece()"));
		ft_memcpy(piece->grid.array[row], line, width);
		if (!is_valid_line(piece->grid.array[row], width, ".*"))
			return (error(piece->grid.array, "Invalid piece detected: read_piece()"));
		ft_strdel(&line);
		++row;
	}
	return (OK);
}
