/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heat_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchen <cchen@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/08 11:01:19 by cchen             #+#    #+#             */
/*   Updated: 2022/05/09 23:18:48 by cchen            ###   ########.fr       */
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

static void	print_heat(t_board *board)
{
	t_dimensions	index;
	t_dimensions	limit;

	limit = board->heat.dimensions;
	index.h = 0;
	while (index.h < limit.h)
	{
		index.w = 0;
		while (index.w < limit.w)
			dprintf(2, "%3s",ft_itoa(board->heat.array[index.h][index.w++]));
		ft_putendl_fd("", 2);
		index.h++;
	}
}

int	set_heat(t_board *board)
{
	if (!make_heat(board))
		return (error(board->grid.array, "Error making heatmap: set_heat()"));
	init_heat(board);
	fill_heat(board);
	print_heat(board);
	return (OK);
}
