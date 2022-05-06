/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchen <cchen@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 12:55:27 by cchen             #+#    #+#             */
/*   Updated: 2022/05/06 17:26:40 by cchen            ###   ########.fr       */
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

int	init(t_map *map, t_piece *piece)
{
	ft_bzero(map, sizeof(*map));
	ft_bzero(piece, sizeof(*piece));
	init_players(map);
	if(!init_array(&(map->map), &(map->dimension), "Plateau"))
		return (error(NULL, "Error reading map data init()"));
	return (OK);
}
