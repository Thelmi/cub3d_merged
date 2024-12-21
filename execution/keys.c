/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krazikho <krazikho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 20:10:49 by krazikho          #+#    #+#             */
/*   Updated: 2024/12/19 20:29:07 by krazikho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static void	move_ver(t_game *game, int keycode)
{
	if (keycode == 13)
	{
		if (game->pl_view == 'N')
			game->pl_y_tile = game->pl_y_tile - 1;
		else if (game->pl_view == 'S')
			game->pl_y_tile = game->pl_y_tile + 1;
		else if (game->pl_view == 'E')
			game->pl_x_tile = game->pl_x_tile + 1;
		else
			game->pl_x_tile = game->pl_x_tile - 1;
	}
	if (keycode == 1)
	{
		if (game->pl_view == 'N')
			game->pl_y_tile = game->pl_y_tile + 1;
		else if (game->pl_view == 'S')
			game->pl_y_tile = game->pl_y_tile - 1;
		else if (game->pl_view == 'E')
			game->pl_x_tile = game->pl_x_tile - 1;
		else
			game->pl_x_tile = game->pl_x_tile + 1;
	}
}

static void	move_hor(t_game *game, int keycode)
{
	if (keycode == 2)
	{
		if (game->pl_view == 'N')
			game->pl_x_tile = game->pl_x_tile + 1;
		else if (game->pl_view == 'S')
			game->pl_x_tile = game->pl_x_tile - 1;
		else if (game->pl_view == 'E')
			game->pl_y_tile = game->pl_y_tile + 1;
		else
			game->pl_y_tile = game->pl_y_tile - 1;
	}
	if (keycode == 0)
	{
		if (game->pl_view == 'N')
			game->pl_x_tile = game->pl_x_tile - 1;
		else if (game->pl_view == 'S')
			game->pl_x_tile = game->pl_x_tile + 1;
		else if (game->pl_view == 'E')
			game->pl_y_tile = game->pl_y_tile - 1;
		else
			game->pl_y_tile = game->pl_y_tile + 1;
	}
}

static void	change_angle_of_view(t_game *game, int keycode)
{
	if (keycode == 123)
		game->pl_view_ang = game->pl_view_ang + 0.1;
	if (keycode == 124)
		game->pl_view_ang = game->pl_view_ang - 0.1;
}

int	key_hook(int keycode, t_game *game)
{
	if (keycode == 13 || keycode == 1)
		move_ver(game, keycode);
	if (keycode == 0 || keycode == 2)
		move_hor(game, keycode);
	if (keycode == 123 || keycode == 124)
		change_angle_of_view(game, keycode);
	if (keycode == 53)
		exit(0);
	draw(game);
	return (1);
}
