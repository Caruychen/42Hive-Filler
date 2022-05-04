/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchen <cchen@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 10:00:00 by cchen             #+#    #+#             */
/*   Updated: 2022/05/04 11:57:38 by cchen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

void init_players(t_map *map)
{
	char	*line;
	char	*p_num;

	if (map->me)
		return ;
	if (get_next_line(0, &line) <= 0)
		return ;
	p_num = ft_strchr(line, 'p');
	if (!p_num++)
		return ;
	if (!(*p_num == '1' || *p_num == '2'))
		return ;
	map->me = 'O' + (*p_num == '2') * 9; 
	map->enemy = 'X' - (*p_num == '2') * 9;
}

void	init(t_map *map)
{
	ft_bzero(map, sizeof(*map));
	init_players(map);
}

int	main(void)
{
	t_map map;
	init(&map);
	dprintf(2, "Testing: %c %c\n", map.me, map.enemy);
	ft_printf("0 0");
	return (0);
}
