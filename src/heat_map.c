/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heat_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchen <cchen@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/08 11:01:19 by cchen             #+#    #+#             */
/*   Updated: 2022/05/08 12:01:44 by cchen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

static int	make_heat(t_board *board)
{
	if (board->heat.array)
		return (OK);
	board->heat.dimensions = board->grid.dimensions;
	return (make_grid(&(board->heat)))
}

static void	init_heat(t_board *board)
{
	t_dimensions	index;
	t_dimensions	limit;

	limit = board->heat.dimensions;
	index.h = 0;
	while (index.h < limit.h)
	{
		index.w = 0;
		while (index.w < limit.w)
		{
		}
		index.h++;
	}
}

static void	fill_heat(t_board *board)
{
	int	row;

	row = 0;
	while (row < board-
}

int	set_heat(t_board *board)
{
	if (!make_heat(board))
		return (error(board->grid.array, "Error making heatmap: set_heat()"));
	init_heat(&(board->heat));
	fill_heat(board);
}
