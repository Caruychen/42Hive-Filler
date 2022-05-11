/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchen <cchen@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 15:42:51 by cchen             #+#    #+#             */
/*   Updated: 2022/05/11 13:58:22 by cchen            ###   ########.fr       */
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

void	cleanup(t_board board, t_piece piece)
{
	if (board.grid.array)
		ft_strdelarray(&board.grid.array);
	if (board.heat.array)
		ft_strdelarray(&board.heat.array);
	if (piece.grid.array)
		ft_strdelarray(&piece.grid.array);
}
