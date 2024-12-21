/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krazikho <krazikho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 14:33:31 by krazikho          #+#    #+#             */
/*   Updated: 2024/12/19 20:33:47 by krazikho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static void	compare_intersections(t_game *game,	int grid_x, int grid_y)
{
	if (game->ray.first_hor_int_c <= game->ray.first_ver_int_c)
		grid_y += game->wall.step_y;
	if (game->ray.first_hor_int_c >= game->ray.first_ver_int_c)
		grid_x += game->wall.step_x;
	while (game->map[grid_y][grid_x] != '1')
	{
		if (game->ray.first_hor_int_c < game->ray.first_ver_int_c)
		{
			grid_y += game->wall.step_y;
			if (game->map[grid_y][grid_x] != '1')
				game->ray.first_hor_int_c += game->ray.c_per_unit_y;
		}
		else
		{
			grid_x += game->wall.step_x;
			if (game->map[grid_y][grid_x] != '1')
				game->ray.first_ver_int_c += game->ray.c_per_unit_x;
		}
	}
}

static double	get_ray_length(t_game *game)
{
	int	grid_x;
	int	grid_y;

	grid_x = game->pl_x;
	grid_y = game->pl_y;
	compare_intersections(game, grid_x, grid_y);
	if (game->ray.first_hor_int_c < game->ray.first_ver_int_c)
	{
		if (sin(game->ray.ray_angle) > 0)
			game->ray.hit_orientation = 0;
		else
			game->ray.hit_orientation = 1;
		return (game->ray.first_hor_int_c);
	}
	else
	{
		if (cos(game->ray.ray_angle) > 0)
			game->ray.hit_orientation = 2;
		else
			game->ray.hit_orientation = 3;
		return (game->ray.first_ver_int_c);
	}
}

static double	cast_ray(t_game *game)
{
	if (sin(game->ray.ray_angle) > 0)
	{
		game->wall.a = game->pl_y_tile - game->pl_y * TILE_SIZE;
		game->wall.step_y = -1;
	}
	else
	{
		game->wall.a = (game->pl_y + 1) * TILE_SIZE - game->pl_y_tile;
		game->wall.step_y = 1;
	}
	if (cos(game->ray.ray_angle) < 0)
	{
		game->wall.b = game->pl_x_tile - game->pl_x * TILE_SIZE;
		game->wall.step_x = -1;
	}
	else
	{
		game->wall.b = (game->pl_x + 1) * TILE_SIZE - game->pl_x_tile;
		game->wall.step_x = 1;
	}
	game->ray.first_hor_int_c = game->wall.a / fabs(sin(game->ray.ray_angle));
	game->ray.first_ver_int_c = game->wall.b / fabs(cos(game->ray.ray_angle));
	game->ray.c_per_unit_y = TILE_SIZE / fabs(sin(game->ray.ray_angle));
	game->ray.c_per_unit_x = TILE_SIZE / fabs(cos(game->ray.ray_angle));
	return (get_ray_length(game));
}

void	draw_walls(t_game *game)
{
	int	x_screen;

	x_screen = 0;
	while (x_screen < WIDTH)
	{
		game->ray.ray_angle = (game->pl_view_ang + FOV_ANGLE / 2) - x_screen
			* (FOV_ANGLE / WIDTH);
		if (game->ray.ray_angle < 0)
			game->ray.ray_angle += 2 * M_PI;
		if (game->ray.ray_angle >= 2 * M_PI)
			game->ray.ray_angle -= 2 * M_PI;
		game->ray.ray_length = cast_ray(game);
		game->wall.wallslice_height = HEIGHT * (1 / (game->ray.ray_length
					/ TILE_SIZE));
		get_we_textures(game);
		get_ns_textures(game);
		draw_wall_slice(game, x_screen);
		x_screen++;
	}
}
