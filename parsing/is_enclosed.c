/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_enclosed.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thelmy <thelmy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 11:24:42 by thelmy            #+#    #+#             */
/*   Updated: 2024/12/19 16:15:18 by thelmy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	is_player(char c)
{
	return (c == 'N' || c == 'W' || c == 'E' || c == 'S');
}

int	check_neighbors(t_game game, int y, int x)
{
	if (t_strlen(game.map[y + 1]) <= (size_t)x
		|| t_strlen(game.map[y - 1]) <= (size_t) x)
		return (0);
	if (game.map[y + 1][x] == ' ' || game.map[y - 1][x] == ' ' ||
		game.map[y][x + 1] == ' ' || game.map[y][x - 1] == ' ')
		return (0);
	return (1);
}

int	is_enclosed(t_game game)
{
	int	i;
	int	j;

	i = 0;
	while (game.map[i])
	{
		j = 0;
		while (game.map[i][j])
		{
			if ((game.map[i][j] == '0' || is_player(game.map[i][j]))
				&& !check_neighbors(game, i, j))
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}
