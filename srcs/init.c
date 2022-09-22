/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tde-nico <tde-nico@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 11:58:51 by tde-nico          #+#    #+#             */
/*   Updated: 2022/09/19 11:34:33 by tde-nico         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_wall_textures(t_game *game)
{
	game->walls[0].img = mlx_xpm_file_to_image(game->mlx,
			game->map->nord, &(game->wall_heights[0]), &(game->wall_widths[0]));
	game->walls[1].img = mlx_xpm_file_to_image(game->mlx,
			game->map->sud, &(game->wall_heights[1]), &(game->wall_widths[1]));
	game->walls[2].img = mlx_xpm_file_to_image(game->mlx,
			game->map->west, &(game->wall_heights[2]), &(game->wall_widths[2]));
	game->walls[3].img = mlx_xpm_file_to_image(game->mlx,
			game->map->east, &(game->wall_heights[3]), &(game->wall_widths[3]));
	game->walls[4].img = mlx_xpm_file_to_image(game->mlx,
			DOOR_PATH, &(game->wall_heights[4]), &(game->wall_widths[4]));
	game->walls[0].addr = mlx_get_data_addr(game->walls[0].img,
			&game->walls[0].bits_per_pixel, &game->walls[0].line_length,
			&game->walls[0].endian);
	game->walls[1].addr = mlx_get_data_addr(game->walls[1].img,
			&game->walls[1].bits_per_pixel, &game->walls[1].line_length,
			&game->walls[1].endian);
	game->walls[2].addr = mlx_get_data_addr(game->walls[2].img,
			&game->walls[2].bits_per_pixel, &game->walls[2].line_length,
			&game->walls[2].endian);
	game->walls[3].addr = mlx_get_data_addr(game->walls[3].img,
			&game->walls[3].bits_per_pixel, &game->walls[3].line_length,
			&game->walls[3].endian);
	game->walls[4].addr = mlx_get_data_addr(game->walls[4].img,
			&game->walls[4].bits_per_pixel, &game->walls[4].line_length,
			&game->walls[4].endian);
}

void	init_minimap(t_game *game)
{
	game->mini.width = game->map->width * MINIMAP_TILE_SIZE + 1;
	game->mini.height = game->map->height * MINIMAP_TILE_SIZE + 1;
	game->mini.x = WIDTH - game->mini.width - MINIMAP_TILE_SIZE;
	game->mini.y = MINIMAP_TILE_SIZE;
	game->mini.map.img = mlx_new_image(game->mlx, game->mini.width,
			game->mini.height);
	game->mini.map.addr = mlx_get_data_addr(game->mini.map.img,
			&game->mini.map.bits_per_pixel, &game->mini.map.line_length,
			&game->mini.map.endian);
}

void	init_game(t_game *game)
{
	game->mlx = mlx_init();
	game->win = mlx_new_window(game->mlx, WIDTH, HEIGHT, NAME);
	game->screen.img = mlx_new_image(game->mlx, WIDTH, HEIGHT);
	game->screen.addr = mlx_get_data_addr(game->screen.img,
			&game->screen.bits_per_pixel, &game->screen.line_length,
			&game->screen.endian);
	init_wall_textures(game);
	init_minimap(game);
}
