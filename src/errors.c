/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchen <cchen@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 15:42:51 by cchen             #+#    #+#             */
/*   Updated: 2022/05/06 15:13:32 by cchen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

int	error(t_map *map, char *msg)
{
	if (map)
	{
		if (map->map)
			ft_strdelarray(&(map->map));
	}
	ft_putendl_fd(msg, 2);
	return (ERROR);
}
