/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_file_parsing.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thelmy <thelmy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 23:04:48 by thelmy            #+#    #+#             */
/*   Updated: 2024/12/18 22:08:32 by thelmy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static char	*trimspaces(char *line, int fd)
{
	int		i;
	int		len;
	char	*str;

	if (!line)
		return (NULL);
	i = 0;
	len = t_strlen(line) - 1;
	while (len >= 0 && is_whitespaces(line[len]))
		len--;
	while (line[i] && is_whitespaces(line[i]))
		i++;
	if (len <= -1)
		return (NULL);
	str = malloc(sizeof(char) * ((len - i) + 2));
	if (!str)
	{
		close(fd);
		return (free(line), NULL);
	}
	ft_strlcpy(str, line + i, (len - i) + 2);
	if (line)
		free(line);
	return (str);
}

static char	*escape_whitespaces(char *line, int fd)
{
	int	i;

	i = 0;
	while (line[i] == ' ')
		i++;
	if (line[i] == '\n')
	{
		free(line);
		line = NULL;
		line = get_next_line(fd);
	}
	return (line);
}

static t_game	file_parsing(t_game game, char *line, int count, int fd)
{
	if (count != 6 || game.floor_hex == game.ceil_hex)
		free_textures_exit(line, game, fd);
	game = map_parsing(game, fd);
	return (game);
}

static t_game	if_textures_parsing(char *line, int *count, t_game game, int fd)
{
	if (line && line[0] != '\0' && ++(*count))
		game = textures_parsing(line, game, fd);
	(free(line), line = NULL);
	return (game);
}

t_game	map_file_parsing(t_game game, int fd)
{
	char	*line;
	int		count;
	int		i;

	line = get_next_line(fd);
	count = 0;
	while (line)
	{
		i = 0;
		while (line[i] == ' ')
			i++;
		if (line[i] == '\n')
		{
			line = escape_whitespaces(line, fd);
			continue ;
		}
		if (line[i] == '\0')
			break ;
		line = trimspaces(line, fd);
		game = if_textures_parsing(line, &count, game, fd);
		if (count == 6)
			break ;
		line = get_next_line(fd);
	}
	return (file_parsing(game, line, count, fd));
}
