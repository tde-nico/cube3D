/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tde-nico <tde-nico@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 11:58:51 by tde-nico          #+#    #+#             */
/*   Updated: 2022/09/08 09:18:10 by tde-nico         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_wall_textures(t_game *game)
{
	game->walls[0] = mlx_xpm_file_to_image(game->mlx,
			game->map->nord, &(game->wall_heights[0]), &(game->wall_widths[0]));
	game->walls[1] = mlx_xpm_file_to_image(game->mlx,
			game->map->sud, &(game->wall_heights[1]), &(game->wall_widths[1]));
	game->walls[2] = mlx_xpm_file_to_image(game->mlx,
			game->map->west, &(game->wall_heights[2]), &(game->wall_widths[2]));
	game->walls[3] = mlx_xpm_file_to_image(game->mlx,
			game->map->east, &(game->wall_heights[3]), &(game->wall_widths[3]));
}

void	init_game(t_game *game)
{
	game->mlx = mlx_init();
	game->win = mlx_new_window(game->mlx, WIDTH, HEIGHT, NAME);
	init_wall_textures(game);
}
