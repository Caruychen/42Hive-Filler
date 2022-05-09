/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heat_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchen <cchen@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/08 11:01:19 by cchen             #+#    #+#             */
/*   Updated: 2022/05/09 16:56:17 by cchen            ###   ########.fr       */
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

/*
static void	scan_neighbours(t_coord coord, t_grid *heat, t_vec *adj)
{
	char	value;
	t_coord	new_coord;

	value = heat->array[coord.row][coord.col];
	new_coord = coord;
	new_coord.row--;
	if (coord.row > 0 && heat->array[new_coord.row][new_coord.col] == -1)
	{
		vec_push(adj, &coord);
		heat->array[new_coord.row][new_coord.col] = value + 1;
	}
}

static void	traverse(t_grid *heat, t_vec *adj)
{
	size_t	index;
	t_coord	coord;

	index = 0;
	while (index < adj->len)
	{
		coord = ((t_coord*) (adj->memory))[index * adj->elem_size];
		scan_neighbours(coord, heat, adj);
		dprintf(2, "%zu, %d, %d, %s, %zu\n", index, coord.row, coord.col, ft_itoa(heat->array[coord.row][coord.col]), adj->len);
		index++;
	}
}
*/

static void	fill_heat(t_board *board)
{
	t_vec	adj;

	vec_new(&adj, 1, sizeof(t_coord));
	init_adj(board->heat, &adj);
	dprintf(2, "%zu %d %d\n", adj.alloc_size, ((t_coord*)(adj.memory))[8].row, ((t_coord*)(adj.memory))[8].col);
//	traverse(&(board->heat), &adj);
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
