/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krazikho <krazikho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 12:15:24 by krazikho          #+#    #+#             */
/*   Updated: 2024/12/21 21:12:37 by krazikho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static void	draw_floornceiling(t_game *game)
{
	unsigned int	*dst;
	unsigned int	i;

	dst = (unsigned int *)game->img.adrs;
	i = 0;
	while (i < WIDTH * HEIGHT / 2)
	{
		*dst = game->ceil_hex;
		dst++;
		i++;
	}
	while (i < WIDTH * HEIGHT)
	{
		*dst = game->floor_hex;
		dst++;
		i++;
	}
}

void	draw(t_game *game)
{
	game->img.img = mlx_new_image(game->mlx_connection, WIDTH, HEIGHT);
	game->img.adrs = mlx_get_data_addr(game->img.img, &game->img.bitsperpixel,
			&game->img.linelen, &game->img.endian);
	draw_floornceiling(game);
	init_ray_values(game);
	init_walls(game);
	draw_walls(game);
	mlx_put_image_to_window(game->mlx_connection, game->mlx_window,
		game->img.img, 0, 0);
	mlx_destroy_image(game->mlx_connection, game->img.img);
}
