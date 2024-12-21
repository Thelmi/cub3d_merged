/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_floor_color_utils.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thelmy <thelmy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 22:41:49 by thelmy            #+#    #+#             */
/*   Updated: 2024/12/18 22:19:04 by thelmy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	is_valid_char(char c)
{
	return (ft_isdigit(c) || c == ',' || c == ' ' || c == '+');
}

int	commas_couter(char *line)
{
	int	comma_count;
	int	i;

	i = 0;
	comma_count = 0;
	while (line[i])
	{
		if (!is_valid_char(line[i]))
		{
			comma_count = 0;
			break ;
		}
		if (line[i] == ',')
			comma_count++;
		i++;
	}
	return (comma_count);
}

int	parse_single_value(char *line, int *i, t_game *game)
{
	int	value;

	while (line[*i] == ' ' || (line[*i] == '+' && ft_isdigit(line[*i + 1])))
		(*i)++;
	if (!ft_isdigit(line[*i]))
		game->free_flag = 1;
	value = atoi(&line[*i]);
	if (value < 0 || value > 255)
		game->free_flag = 1;
	while (ft_isdigit(line[*i]))
		(*i)++;
	return (value);
}

t_game	assigning_fl_rgb(t_game game, int *values)
{
	game.flr_r = values[0];
	game.flr_g = values[1];
	game.flr_b = values[2];
	game.floor_hex = game.flr_r * pow(256, 2)
		+ (game.flr_g * 256) + game.flr_b;
	return (game);
}

void	check_last_characters(char *line, t_game *game, int i)
{
	while (line[i] == ' ')
		i++;
	if (line[i])
		game->free_flag = 1;
}
