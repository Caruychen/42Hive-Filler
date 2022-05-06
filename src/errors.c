/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchen <cchen@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 15:42:51 by cchen             #+#    #+#             */
/*   Updated: 2022/05/06 16:36:12 by cchen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

int	error(char **array, char *msg)
{
	if (array)
		ft_strdelarray(&array);
	ft_putendl_fd(msg, 2);
	return (ERROR);
}
