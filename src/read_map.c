/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchen <cchen@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 13:10:11 by cchen             #+#    #+#             */
/*   Updated: 2022/05/08 10:03:16 by cchen            ###   ########.fr       */
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
	return (read_input(&(board->grid), 4, ".oOxX"));
}
