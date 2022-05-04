/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_board.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchen <cchen@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 13:10:11 by cchen             #+#    #+#             */
/*   Updated: 2022/05/04 13:54:42 by cchen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

static int	read_plateau(char **plateau)
{
	char	*line;

	if (get_next_line(STDIN, &line) <= 0)
		return (ERROR);
	*plateau = ft_strsplit(line, ' ');
	ft_strdel(&line);
	return (plateau != NULL);
}

static int	get_size(t_map *map)
{
	char	**plateau;

	if (!read_plateau(plateau))
		return (ERROR);
	if (ft_strcmp("Plateau", plateau[0]))
	{
		ft_strdelarray(&plateau);
		return (ERROR);
	}
	board->height = ft_atoi(plateau[1]);
	board->width = ft_atoi(plateau[2]);
	ft_strdelarray(&plateau);
	if (!board->height || !board->width)
		return (ERROR);
	return (OK);
}

int init_map(t_map *map)
{
	char *line;

	get_size(map);
	if (get_next_line(0, &line) <= 0)
		return (ERROR);
	ft_strdel(&line);
	if (!map->map)
		map->map = (char **)ft_memalloc(sizeof(char *) * (map->height + 1));
}
