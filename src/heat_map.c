/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heat_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchen <cchen@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/08 11:01:19 by cchen             #+#    #+#             */
/*   Updated: 2022/05/09 12:01:48 by cchen            ###   ########.fr       */
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
			ft_putstr_fd(ft_itoa(board->heat.array[index.h][index.w++]), 2);
		ft_putendl_fd("", 2);
		index.h++;
	}
}

static int	is_exposed_edge(t_grid heat, t_coord coord)
{
	if (heat.array[coord.row][coord.col] != 0)
		return (0);
	if (coord.row > 0 && heat.array[coord.row - 1][coord.col] == -1)
		return (1);
	if (coord.col > 0 && heat.array[coord.row][coord.col - 1] == -1)
		return (1);
	if (coord.row < heat.dimensions.h - 1 && heat.array[coord.row + 1][coord.col] == -1)
		return (1);
	if (coord.col < heat.dimensions.w - 1 && heat.array[coord.row][coord.col + 1] == -1)
		return (1);
	return (0);
}

static void	init_adj(t_grid heat, t_vec *adj)
{
	t_dimensions	limit;
	t_coord			coord;

	limit = heat.dimensions;
	coord.row = 0;
	while (coord.row < limit.h)
	{
		coord.col = 0;
		while (coord.col < limit.w)
		{
			if (is_exposed_edge(heat, coord))
				vec_push(adj, &coord);
			coord.col++;
		}
		coord.row++;
	}
}

static void	traverse(t_grid *heat, t_vec *adj)
{
	size_t	index;
	t_coord	current;

	index = 0;
	while (index < adj->len)
	{
		current = *((t_coord*) (adj.memory));
		index++;
	}
}

static void	fill_heat(t_board *board)
{
	t_vec	adj;

	vec_new(&adj, 1, sizeof(t_coord));
	init_adj(board->heat, &adj);
//	traverse(&(board->heat), &adj);
	dprintf(2, "%d, %d\n", ((t_coord*) adj.memory)->row, ((t_coord*)(adj.memory))->col);
	t_coord	current;
	dprintf(2, "%d, %d\n", current.row, current.col);
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
