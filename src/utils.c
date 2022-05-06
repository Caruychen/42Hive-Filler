/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_size.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchen <cchen@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/06 13:50:14 by cchen             #+#    #+#             */
/*   Updated: 2022/05/06 15:12:02 by cchen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

int	get_dimensions(t_dimension *dimension, char *name)
{
	char		*line;

	if (get_next_line(STDIN, &line) <= 0)
		return (error(NULL, "Memory allocation error: get_dimensions()"));
	if (!ft_strstr(line, name))
		return (error(NULL, "Error reading dimension: get_dimensions()"));
	dimension->h = ft_atoi(ft_strchr(line, ' '));
	dimension->w = ft_atoi(ft_strrchr(line, ' '));
	ft_strdel(&line);
	if (!dimension->w || !dimension->h)
		return (error(NULL, "Error reading %s: get_dimensions()"));
	return (OK);
}
