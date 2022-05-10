/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heat_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchen <cchen@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/08 11:01:19 by cchen             #+#    #+#             */
/*   Updated: 2022/05/10 20:33:36 by cchen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

static int	make_heat(t_board *board)
{
	if (board->heat.array)
		return (OK);
	board->heat.dimensions = board->grid.dimensions;
	return (make_grid(&(board->heat)));
}

static void	init_heat(t_board *board)
{
	t_dimensions	limit;
	t_dimensions	index;
	char			**grid;
	char			enemy;

	grid = board->grid.array;
	enemy = board->enemy;
	limit = board->heat.dimensions;
	index.h = 0;
	while (index.h < limit.h)
	{
		index.w = 0;
		while (index.w < limit.w)
		{
			board->heat.array[index.h][index.w]
				= -(grid[index.h][index.w] != enemy);
			index.w++;
		}
		index.h++;
	}
}

static int	fill_heat(t_board *board)
{
	t_vec	queue;

	if (vec_new(&queue, 1, sizeof(t_coord)) == -1)
		return (error(NULL, "Error allocating queue: fill_heat()"));
	if (init_queue(board->heat, &queue) == -1)
		return (error(NULL, "Error initializing queue: fill_heat()"));
	scan_queue(&(board->heat), &queue);
	vec_free(&queue);
	return (OK);
}

int	set_heat(t_board *board)
{
	if (!make_heat(board))
		return (error(board->grid.array, "Error making heatmap: set_heat()"));
	init_heat(board);
	if (!fill_heat(board))
		return (error(board->grid.array, "Error filling heatmap: set_heat()"));
	return (OK);
}
