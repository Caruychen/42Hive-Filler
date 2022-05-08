/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_piece.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchen <cchen@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/06 17:12:31 by cchen             #+#    #+#             */
/*   Updated: 2022/05/08 10:06:20 by cchen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

static int	make_piece(t_piece *piece)
{
	if (piece->grid.array)
		ft_strdelarray(&(piece->grid.array));
	return (make_grid(&(piece->grid), "Piece"));
}

int	read_piece(t_piece *piece)
{
	if (!make_piece(piece))
		return (error(NULL, "Error making piece: read_piece()"));
	return (set_grid(&(piece->grid), 0, ".*"));
}
