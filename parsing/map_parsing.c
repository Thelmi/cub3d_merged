/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thelmy <thelmy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 01:23:17 by thelmy            #+#    #+#             */
/*   Updated: 2024/12/19 16:14:34 by thelmy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

t_game	newline_handler(char *str, char *s, t_game game, int fd)
{
	if (!str || (str[0] == '\n' && game.newline == 0))
		game.newline = 1;
	else if (str[0] != '\n' && game.newline == 1)
	{
		printf("Error\n new line in the middle of the map\n");
		if (str)
			free(str);
		if (s)
			free(s);
		free_textures(game);
		close(fd);
		exit(1);
	}
	return (game);
}

static char	*read_map_free(char *read, t_game game, int fd)
{
	char	*read_next;

	read_next = NULL;
	while (read)
	{
		read_next = get_next_line(fd);
		if (read_next == NULL)
			break ;
		game = newline_handler(read_next, read, game, fd);
		letters_checker(read_next, read, game, fd);
		read = t_strjoin(read, read_next);
		free (read_next);
	}
	return (read);
}

void	valid_all_ones(char *read, t_game game, int fd)
{
	int	i;

	i = 0;
	while (read[i] == ' ')
		i++;
	while (read[i])
	{
		if (read[i] != '1' && read[i] != '\n' && read[i] != ' ')
		{
			free(read);
			free_textures(game);
			close(fd);
			printf("Error\n border is not valid\n");
			exit(1);
		}
		i++;
	}
}

static char	*nl_escaper(char *str, t_game game, int fd)
{
	if (!str)
	{
		if (str)
			free(str);
		free_textures(game);
		close(fd);
		printf("Error\n where is the map\n");
		exit(1);
	}
	while (str[0] == '\n')
	{
		free(str);
		str = get_next_line(fd);
		if (!str)
		{
			if (str)
				free(str);
			free_textures(game);
			close(fd);
			printf("Error\n where is the map\n");
			exit(1);
		}
	}
	return (str);
}

t_game	map_parsing(t_game game, int fd)
{
	char	*read;
	char	**str;

	read = get_next_line(fd);
	read = nl_escaper(read, game, fd);
	valid_all_ones(read, game, fd);
	read = read_map_free(read, game, fd);
	str = ft_split(read, '\n');
	game = locate_check_players(str, game, fd, read);
	game.map = str;
	if (!is_enclosed(game))
	{
		free_textures(game);
		free_map(game);
		free(read);
		close (fd);
		printf("Error\n not surrounded by walls\n");
		exit(1);
	}
	free(read);
	return (game);
}
