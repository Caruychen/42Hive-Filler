/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchen <cchen@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/06 13:50:14 by cchen             #+#    #+#             */
/*   Updated: 2022/05/08 10:02:51 by cchen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

static int	set_dimensions(t_dimensions *dimensions, char *name)
{
	char		*line;

	if (get_next_line(STDIN, &line) <= 0)
		return (error(NULL, "Memory allocation error: get_dimensions()"));
	if (!ft_strstr(line, name))
	{
		ft_strdel(&line);
		return (error(NULL, "Error, dimension category not found: get_dimensions()"));
	}
	dimensions->h = ft_atoi(ft_strchr(line, ' '));
	dimensions->w = ft_atoi(ft_strrchr(line, ' '));
	ft_strdel(&line);
	if (!dimensions->w || !dimensions->h)
		return (error(NULL, "Error, invalid dimensions: get_dimensions()"));
	return (OK);
}

int	make_grid(t_grid *grid, char *name)
{
	int		row;
	t_dimensions	*dims;

	dims = &(grid->dimensions);
	if (!set_dimensions(dims, name)) 
		return (error(NULL, "Error reading dimensions: init_array()"));
	grid->array = (char **)malloc(sizeof(char *) * (dims->h + 1));
	if (!grid->array)
		return (error(NULL, "Error allocating data array: init_array()"));
	row = 0;
	while (row < dims->h)
	{
		grid->array[row] = (char *)ft_strnew(sizeof(char) * dims->w);
		if (!grid->array[row])
			return (error(grid->array, "Error allocating data row: init_array()"));
		row++;
	}
	return (OK);
}

int	skip_line(void)
{
	char	*line;

	if (get_next_line(0, &line) <= 0)
		return (ERROR);
	ft_strdel(&line);
	return (OK);
}

int	is_valid_line(char *line, int width, char *sample)
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

int	read_input(t_grid *grid, int start, char *sample)
{
	char	*line;
	int	height;
	int	width;
	int	row;

	height = grid->dimensions.h;
	width = grid->dimensions.w;
	row = 0;
	while (row < height)
	{
		if (get_next_line(0, &line) <= 0)
			return (error(grid->array, "Error reading input line: read_input()"));
		ft_memcpy(grid->array[row], line + start, width);
		if (!is_valid_line(grid->array[row], width, sample))
			return (error(grid->array, "Invalid board detected: read_input()"));
		ft_strdel(&line);
		++row;
	}
	return (OK);
}