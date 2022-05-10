/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heat_adj_queues.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchen <cchen@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 22:52:07 by cchen             #+#    #+#             */
/*   Updated: 2022/05/10 20:36:28 by cchen            ###   ########.fr       */
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

static int	fill(char value, t_coord new_coord, t_grid *heat, t_vec *queue)
{
	if (heat->array[new_coord.row][new_coord.col] != -1)
		return (OK);
	if (vec_push(queue, &new_coord) == -1)
		return (error(NULL, "Memory allocation error in fill()"));
	heat->array[new_coord.row][new_coord.col] = value + 1;
	return (OK);
}

static int	scan_neighbours(t_coord coord, t_grid *heat, t_vec *queue)
{
	char	value;
	t_coord	new_coord;

	value = heat->array[coord.row][coord.col];
	new_coord = (t_coord){.row = coord.row - 1, .col = coord.col};
	if (coord.row > 0 && !fill(value, new_coord, heat, queue))
		return (error(NULL, "Error filling neighbour: scan_neighbours()"));
	new_coord = (t_coord){.row = coord.row, .col = coord.col - 1};
	if (coord.col > 0 && !fill(value, new_coord, heat, queue))
		return (error(NULL, "Error filling neighbour: scan_neighbours()"));
	new_coord = (t_coord){.row = coord.row + 1, .col = coord.col};
	if (coord.row < heat->dimensions.h -1
		&& !fill(value, new_coord, heat, queue))
		return (error(NULL, "Error filling neighbour: scan_neighbours()"));
	new_coord = (t_coord){.row = coord.row, .col = coord.col + 1};
	if (coord.col < heat->dimensions.w -1
		&& !fill(value, new_coord, heat, queue))
		return (error(NULL, "Error filling neighbour: scan_neighbours()"));
	return (OK);
}

int	init_queue(t_grid heat, t_vec *queue)
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
			if (is_exposed_edge(heat, coord) && vec_push(queue, &coord) == -1)
				return (error(NULL,
						"Error allocating queue memory: init_queue()"));
			coord.col++;
		}
		coord.row++;
	}
	return (OK);
}

int	scan_queue(t_grid *heat, t_vec *queue)
{
	size_t	index;
	t_coord	coord;

	index = 0;
	while (index < queue->len)
	{
		coord = ((t_coord *)(queue->memory))[index];
		if(!scan_neighbours(coord, heat, queue))
			return (error(NULL,"Error scanning neighbours: scan_queue()"));
		index++;
	}
	return (OK);
}
