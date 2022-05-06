/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchen <cchen@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/06 13:50:14 by cchen             #+#    #+#             */
/*   Updated: 2022/05/06 17:15:06 by cchen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

int	skip_line(void)
{
	char	*line;

	if (get_next_line(0, &line) <= 0)
		return (ERROR);
	ft_strdel(&line);
	return (OK);
}

int	get_dimensions(t_dimension *dimension, char *name)
{
	char		*line;

	if (get_next_line(STDIN, &line) <= 0)
		return (error(NULL, "Memory allocation error: get_dimensions()"));
	if (!ft_strstr(line, name))
	{
		ft_strdel(&line);
		return (error(NULL, "Error, dimension category not found: get_dimensions()"));
	}
	dimension->h = ft_atoi(ft_strchr(line, ' '));
	dimension->w = ft_atoi(ft_strrchr(line, ' '));
	ft_strdel(&line);
	if (!dimension->w || !dimension->h)
		return (error(NULL, "Error, invalid dimensions: get_dimensions()"));
	return (OK);
}

int	init_array(char ***array, t_dimension *dimensions, char *name)
{
	int	row;

	if (*array)
		return (OK);
	if (!get_dimensions(dimensions, name)) 
		return (error(NULL, "Error reading dimensions: init_array()"));
	*array = (char **)malloc(sizeof(char *) * (dimensions->h + 1));
	if (!*array)
		return (error(NULL, "Error allocating data array: init_array()"));
	row = 0;
	while (row < dimensions->h)
	{
		(*array)[row] = (char *)ft_strnew(sizeof(char) * dimensions->w);
		if (!(*array)[row])
			return (error(*array, "Error allocating data row: init_array()"));
		row++;
	}
	return (OK);
}
