/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heat_fill.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchen <cchen@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 22:52:07 by cchen             #+#    #+#             */
/*   Updated: 2022/05/09 23:15:56 by cchen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

static int	is_exposed_edge(t_grid heat, t_coord coord)
{
	if (heat.array[coord.row][coord.col] != 0)
		return (0);
	if (coord.row > 0 && heat.array[coord.row - 1][coord.col] == -1)
		return (1);
	if (coord.col > 0 && heat.array[coord.row][coord.col - 1] == -1)
		return (1);
	if (coord.row < heat.dimensions.h - 1
		&& heat.array[coord.row + 1][coord.col] == -1)
		return (1);
	if (coord.col < heat.dimensions.w - 1
		&& heat.array[coord.row][coord.col + 1] == -1)
		return (1);
	return (0);
}

static void	enqueue(t_coord coord, t_grid *heat, t_vec *adj)
{
	char	value;
	t_coord	new_coord;

	value = heat->array[coord.row][coord.col];
	new_coord = (t_coord){.row = coord.row - 1, .col = coord.col};
	if (coord.row > 0 && heat->array[new_coord.row][new_coord.col] == -1)
	{
		vec_push(adj, &new_coord);
		heat->array[new_coord.row][new_coord.col] = value + 1;
	}
	new_coord = (t_coord){.row = coord.row, .col = coord.col - 1};
	if (coord.col > 0 && heat->array[new_coord.row][new_coord.col] == -1)
	{
		vec_push(adj, &new_coord);
		heat->array[new_coord.row][new_coord.col] = value + 1;
	}
	new_coord = (t_coord){.row = coord.row + 1, .col = coord.col};
	if (coord.row < heat->dimensions.h -1
		&& heat->array[new_coord.row][new_coord.col] == -1)
	{
		vec_push(adj, &new_coord);
		heat->array[new_coord.row][new_coord.col] = value + 1;
	}
	new_coord = (t_coord){.row = coord.row, .col = coord.col + 1};
	if (coord.col < heat->dimensions.w -1
		&& heat->array[new_coord.row][new_coord.col] == -1)
	{
		vec_push(adj, &new_coord);
		heat->array[new_coord.row][new_coord.col] = value + 1;
	}
}

static int	init_queue(t_grid heat, t_vec *adj)
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
			if (is_exposed_edge(heat, coord) && vec_push(adj, &coord) == -1)
				return (error(NULL,
						"Error allocating queue memory: init_queue()"));
			coord.col++;
		}
		coord.row++;
	}
	return (OK);
}

static void	scan_queue(t_grid *heat, t_vec *adj)
{
	size_t	index;
	t_coord	coord;

	index = 0;
	while (index < adj->len)
	{
		coord = ((t_coord *)(adj->memory))[index];
		enqueue(coord, heat, adj);
		index++;
	}
}

int	fill_heat(t_board *board)
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
