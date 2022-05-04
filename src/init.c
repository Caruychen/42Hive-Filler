/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchen <cchen@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 12:55:27 by cchen             #+#    #+#             */
/*   Updated: 2022/05/04 13:17:34 by cchen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

static void	init_players(t_map *map)
{
	char	*line;
	char	*p_num;

	if (map->me)
		return ;
	if (get_next_line(STDIN, &line) <= 0)
		return ;
	p_num = ft_strchr(line, 'p');
	if (!p_num++)
		return ;
	if (!(*p_num == '1' || *p_num == '2'))
		return ;
	map->me = 'O' + (*p_num == '2') * 9;
	map->enemy = 'X' - (*p_num == '2') * 9;
	ft_strdel(&line);
}

void	init(t_map *map)
{
	ft_bzero(map, sizeof(*map));
	init_players(map);
	init_map(map);
}
