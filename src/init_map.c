/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchen <cchen@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 13:10:11 by cchen             #+#    #+#             */
/*   Updated: 2022/05/05 14:32:50 by cchen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

static char**	read_plateau(void)
{
	char	*line;
	char	**plateau;

	if (get_next_line(STDIN, &line) <= 0)
		return (NULL);
	plateau = ft_strsplit(line, ' ');
	ft_strdel(&line);
	if (!plateau)
		return (NULL);
	return (plateau);
}

static int	get_size(t_map *map)
{
	char	**plateau;

	plateau = read_plateau();
	if (!plateau)
		return (ERROR);
	if (ft_strcmp("Plateau", plateau[0]))
	{
		ft_strdelarray(&plateau);
		return (ERROR);
	}
	map->height = ft_atoi(plateau[1]);
	map->width = ft_atoi(plateau[2]);
	ft_strdelarray(&plateau);
	if (!map->height || !map->width)
		return (ERROR);
	return (OK);
}

static int	skip_line(void)
{
	char	*line;

	if (get_next_line(0, &line) <= 0)
		return (ERROR);
	ft_strdel(&line);
	return (OK);
}

static int	is_valid_map(char *row, int width)
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

int init_map(t_map *map)
{
	char	*line;
	int		row;

	get_size(map);
	skip_line();
	if (!map->map)
		map->map = (char **)ft_memalloc(sizeof(char *) * (map->height + 1));
	row = 0;
	while (row < map->height)
	{
		if (get_next_line(0, &line) <= 0)
		{
			ft_strdelarray(&(map->map));
			return (ERROR);
		}
		map->map[row] = ft_strsub(line, 4, map->width);
		ft_strdel(&line);
		if (!is_valid_map(map->map[row], map->width))
		{
			ft_strdelarray(&(map->map));
			return (ERROR);
		}
	}
	return (OK);
}
