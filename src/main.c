/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchen <cchen@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 10:00:00 by cchen             #+#    #+#             */
/*   Updated: 2022/05/06 17:16:22 by cchen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

void debug(t_map map)
{
	int row = 0;
	while (row < map.dimension.h)
	{
		ft_putendl_fd(map.map[row], 2);
		row++;
	}
}

int	main(void)
{
	t_map	map;
	t_piece	piece;

	if (!init(&map, &piece))
		return (0);
	while (1)
	{
		if (!read_map(&map))
			return (0);
		if (!read_piece(&piece))
			return (0);
		ft_printf("0 0");
	}
	return (0);
}
