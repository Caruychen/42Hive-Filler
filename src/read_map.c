/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchen <cchen@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 13:10:11 by cchen             #+#    #+#             */
/*   Updated: 2022/05/06 14:53:39 by cchen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

static int	skip_line(void)
{
	char	*line;

	if (get_next_line(0, &line) <= 0)
		return (ERROR);
	ft_strdel(&line);
	return (OK);
}

static int	is_valid(char *row, int width)
{
	if (ft_strlen(row) != (size_t) width)
		return (ERROR);
	while (*row)
	{
		if (!ft_strchr(".oOxX", *row))
			return (ERROR);
		++row;
	}
	return (OK);
}

int read_map(t_map *map)
{
	char	*line;
	int		row;
	int		height;
	int		width;

	skip_line();
	height = map->dimension.h;
	width = map->dimension.w;
	row = 0;
	while (row < height)
	{
		if (get_next_line(0, &line) <= 0)
			return (error(map, "Error reading input line: read_map.c"));
		ft_memcpy(map->map[row], line + 4, width);
		if (!is_valid(map->map[row], width))
			return (error(map, "Invalid map detected: read_map.c"));
		ft_strdel(&line);
		++row;
	}
	return (OK);
}
