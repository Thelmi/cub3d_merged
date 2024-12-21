/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parsing_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thelmy <thelmy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 05:34:18 by thelmy            #+#    #+#             */
/*   Updated: 2024/12/19 16:07:01 by thelmy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	last_line_valid(char *read_next, char *read, t_game game, int fd)
{
	int	i;

	i = 0;
	while (read_next[i] == ' ')
		i++;
	while (read_next[i])
	{
		if (read_next[i] && read_next[i] != '1'
			&& read_next[i] != '\n' && read_next[i] != ' ')
		{
			printf("Error\n Map is invalid (%s)\n", read_next);
			if (read_next)
				free(read_next);
			if (read)
				free(read);
			free_textures(game);
			close(fd);
			exit(1);
		}
		i++;
	}
}

void	letters_exit(char *read_next, char *read, t_game game, int fd)
{
	if (!game.newline)
	{
		printf("Error\n Map is invalid (%s)\n", read_next);
		if (read_next)
			free(read_next);
		if (read)
			free(read);
		free_textures(game);
		close(fd);
		exit(1);
	}
}

static int	is_valid_map_char(char c)
{
	return (c == ' ' || c == '0' || c == '1'
		|| c == 'N' || c == 'S' || c == 'E' || c == 'W' || c == '\n');
}

void	letters_checker(char *read_next, char *read, t_game game, int fd)
{
	int	i;
	int	len;

	i = 0;
	len = t_strlen(read_next) - 2;
	while (read_next[i] == ' ')
		i++;
	if (read_next[i] != '1')
		letters_exit(read_next, read, game, fd);
	if (!ft_strchr(read_next, '\n'))
		last_line_valid(read_next, read, game, fd);
	else if (t_strlen(read_next) > 2)
	{
		while (read_next[len] == ' ')
			len--;
		if (read_next[len] != '1')
			letters_exit(read_next, read, game, fd);
	}
	while (read_next[i])
	{
		if (!is_valid_map_char(read_next[i]))
			letters_exit(read_next, read, game, fd);
		i++;
	}
}
