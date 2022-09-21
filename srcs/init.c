/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tde-nico <tde-nico@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 11:58:51 by tde-nico          #+#    #+#             */
/*   Updated: 2022/09/07 12:41:52 by tde-nico         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_game(t_game *game)
{
	game->mlx = mlx_init();
	game->win = mlx_new_window(game->mlx, WIDTH, HEIGHT, NAME);
	game->minimap.map = mlx_new_image(game->mlx, game->map->width
			* MINIMAP_TILE_SIZE, game->map->height * MINIMAP_TILE_SIZE);
	game->minimap.addr = mlx_get_data_addr(game->minimap.map,
			&game->minimap.bits_per_pixel, &game->minimap.line_length,
			&game->minimap.endian);
}
