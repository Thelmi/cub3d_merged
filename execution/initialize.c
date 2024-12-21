/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krazikho <krazikho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 13:05:09 by krazikho          #+#    #+#             */
/*   Updated: 2024/12/19 19:13:12 by krazikho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	init_player_view_and_position(t_game *game)
{
	game->pl_x_tile = (game->pl_x * TILE_SIZE) + (TILE_SIZE / 2);
	game->pl_y_tile = (game->pl_y * TILE_SIZE) + (TILE_SIZE / 2);
	if (game->pl_view == 'E')
		game->pl_view_ang = 0;
	else if (game->pl_view == 'N')
		game->pl_view_ang = M_PI / 2;
	else if (game->pl_view == 'W')
		game->pl_view_ang = M_PI;
	else if (game->pl_view == 'S')
		game->pl_view_ang = 3 * M_PI / 2;
}

void	init_ray_values(t_game *game)
{
	game->ray.ray_angle = 0.0;
	game->ray.ray_length = 0.0;
	game->ray.ray_init_x = 0.0;
	game->ray.ray_init_y = 0.0;
	game->ray.c_per_unit_x = 0.0;
	game->ray.c_per_unit_y = 0.0;
	game->ray.first_hor_int_c = 0.0;
	game->ray.first_ver_int_c = 0.0;
	game->ray.hit_orientation = 0;
}

void	init_walls(t_game *game)
{
	game->wall.start_y = 0;
	game->wall.end_y = 0;
	game->wall.wallslice_height = 0;
	game->wall.texture_step = 0.0;
	game->wall.tex_x = 0.0;
	game->wall.tex_y = 0.0;
}
