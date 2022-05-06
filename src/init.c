/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchen <cchen@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 12:55:27 by cchen             #+#    #+#             */
/*   Updated: 2022/05/06 15:13:35 by cchen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

static int	init_players(t_map *map)
{
	char	*line;
	char	*p_num;

	if (map->me)
		return (OK);
	if (get_next_line(STDIN, &line) <= 0)
		return (error(NULL, "Error reading input line: init_players.c"));
	p_num = ft_strchr(line, 'p');
	if (!p_num++ || !(*p_num == '1' || *p_num == '2'))
	{
		ft_strdel(&line);
		return (error(NULL, "Failed to detect players: init_players.c"));
	}
	map->me = 'O' + (*p_num == '2') * 9;
	map->enemy = 'X' - (*p_num == '2') * 9;
	ft_strdel(&line);
	return (OK);
}

static int	init_data(char **array, t_dimension *dimensions, char *name)
{
	int	row;

	if (array)
		return (OK);
	if (!get_dimensions(dimensions, name)) 
		return (error(NULL, "Error reading dimensions: init_data()"));
	array = (char **)malloc(sizeof(char *) * (dimensions->h + 1));
	if (!array)
		return (error(NULL, "Error allocating data array: init_data()"));
	row = 0;
	while (row < dimensions->h)
	{
		array[row] = (char *)ft_strnew(sizeof(char) * dimensions->w);
		if (!array[row])
			return (error(NULL, "Error allocating data row: init_data()"));
		row++;
	}
	return (OK);
}

int	init(t_map *map, t_piece *piece)
{
	ft_bzero(map, sizeof(*map));
	init_players(map);
	if(!init_data(map->map, &(map->dimension), "Plateau"))
		return (error(NULL, "Error reading map data"));
	return (OK);
}
