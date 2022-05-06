/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_piece.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchen <cchen@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/06 17:12:31 by cchen             #+#    #+#             */
/*   Updated: 2022/05/06 17:29:48 by cchen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	read_piece(t_piece *piece)
{
	char	*line;
	int		row;
	int		height;
	int		width;

	if(!init_array(&(piece->pc), &(piece->dimension), "Piece"))
		return (error(NULL, "Error reading piece data: read_piece()"));
	height = piece->dimension.h;
	width = piece->dimension.w;
	row = 0;
	while (row < height)
	{
		if (get_next_line(0, &line) <= 0)
			return (error(piece->pc, "Error reading input line: read_piece()"));
		ft_memcpy(piece->pc[row], line, width);
		if (!is_valid(piece->pc[row], width))
			return (error(piece->pc, "Invalid piece detected: read_piece()"));
		ft_strdel(&line);
		++row;
	}
	return (OK);
}
