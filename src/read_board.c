/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchen <cchen@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 13:10:11 by cchen             #+#    #+#             */
/*   Updated: 2022/05/08 10:06:34 by cchen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

static int	make_board(t_board *board)
{
	if (!board->grid.array)
		return (make_grid(&(board->grid), "Plateau"));
	skip_line();
	return (OK);
}

int read_board(t_board *board)
{
	if (!make_board(board))
		return (error(NULL, "Error making board: read_board()"));
	skip_line();
	return (set_grid(&(board->grid), 4, ".oOxX"));
}
