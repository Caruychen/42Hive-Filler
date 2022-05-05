/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchen <cchen@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 12:55:27 by cchen             #+#    #+#             */
/*   Updated: 2022/05/05 16:02:16 by cchen            ###   ########.fr       */
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

void	init(t_map *map)
{
	ft_bzero(map, sizeof(*map));
	init_players(map);
	init_map(map);
}
