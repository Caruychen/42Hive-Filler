/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchen <cchen@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 13:10:11 by cchen             #+#    #+#             */
/*   Updated: 2022/05/07 16:09:14 by cchen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

static int	make_board(t_board *board)
{
	if (!board->grid.array)
		return (make_array(&(board->grid), "Plateau"));
	skip_line();
	return (OK);
}

int read_board(t_board *board)
{
	char	*line;
	int		row;
	int		height;
	int		width;

	if (!make_board(board))
		return (error(NULL, "Error making board: read_board()"));
	skip_line();
	height = board->grid.dimensions.h;
	width = board->grid.dimensions.w;
	row = 0;
	while (row < height)
	{
		if (get_next_line(0, &line) <= 0)
			return (error(board->grid.array, "Error reading input line: read_board()"));
		ft_memcpy(board->grid.array[row], line + 4, width);
		if (!is_valid_line(board->grid.array[row], width, ".oOxX"))
			return (error(board->grid.array, "Invalid board detected: read_board()"));
		ft_strdel(&line);
		++row;
	}
	return (OK);
}
