/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchen <cchen@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/06 13:50:14 by cchen             #+#    #+#             */
/*   Updated: 2022/05/11 10:17:39 by cchen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

int	set_dimensions(t_dimensions *dimensions, char *name)
{
	char		*line;

	if (get_next_line(STDIN, &line) <= 0)
		return (error(NULL, "Memory allocation error: get_dimensions()"));
	if (!ft_strstr(line, name))
	{
		ft_strdel(&line);
		return (error(NULL, "Failed to find dimension: get_dimensions()"));
	}
	dimensions->h = ft_atoi(ft_strchr(line, ' '));
	dimensions->w = ft_atoi(ft_strrchr(line, ' '));
	ft_strdel(&line);
	if (!dimensions->w || !dimensions->h)
		return (error(NULL, "Error, invalid dimensions: get_dimensions()"));
	return (OK);
}

int	make_grid(t_grid *grid)
{
	int				row;
	t_dimensions	*dims;

	dims = &(grid->dimensions);
	grid->array = (char **)ft_memalloc(sizeof(char *) * (dims->h + 1));
	if (!grid->array)
		return (error(NULL, "Error allocating data array: make_grid()"));
	row = 0;
	while (row < dims->h)
	{
		grid->array[row] = (char *)ft_strnew(sizeof(char) * dims->w);
		if (!grid->array[row])
			return (error(grid->array, "Error allocating row: make_grid()"));
		row++;
	}
	return (OK);
}

static int	is_valid_line(char *line, int width, char *sample)
{
	if (ft_strlen(line) != (size_t) width)
		return (ERROR);
	while (*line)
	{
		if (!ft_strchr(sample, *line))
			return (ERROR);
		++line;
	}
	return (OK);
}

int	set_grid(t_grid *grid, int start, char *sample)
{
	char	*line;
	int		height;
	int		width;
	int		row;

	height = grid->dimensions.h;
	width = grid->dimensions.w;
	row = 0;
	while (row < height)
	{
		if (get_next_line(0, &line) <= 0)
			return (error(grid->array, "Error reading line: set_grid()"));
		ft_memcpy(grid->array[row], line + start, width);
		if (!is_valid_line(grid->array[row], width, sample))
			return (error(grid->array, "Invalid board detected: set_grid()"));
		ft_strdel(&line);
		++row;
	}
	return (OK);
}

int	skip_line(void)
{
	char	*line;
	int	res;

	res = get_next_line(0, &line);
	if (res < 0)
		return (ERROR);
	if (res == 0)
		return (OK);
	ft_strdel(&line);
	return (OK);
}
