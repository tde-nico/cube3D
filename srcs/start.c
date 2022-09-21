/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tde-nico <tde-nico@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/08 09:36:45 by tde-nico          #+#    #+#             */
/*   Updated: 2022/09/08 12:41:41 by tde-nico         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	start_player(t_game *game)
{
	char	dir;
	int		x;
	int		y;

	x = (int)game->map->player_pos.x;
	y = (int)game->map->player_pos.y;
	game->player.pos.x = x;
	game->player.pos.y = y;
	dir = game->map->map[y][x];
	game->player.dir.x = 0;
	game->player.dir.y = 0;
	if (dir == PLAYER_CHARACTERS[0])
		game->player.dir.y = -1;
	else if (dir == PLAYER_CHARACTERS[1])
		game->player.dir.y = 1;
	else if (dir == PLAYER_CHARACTERS[2])
		game->player.dir.x = -1;
	else if (dir == PLAYER_CHARACTERS[3])
		game->player.dir.x = 1;
	game->player.plane.x = 0;
	game->player.plane.y = PLAYER_FOV;
	game->player.mov_dir.x = 0;
	game->player.mov_dir.y = 0;
	game->player.rot_dir = 0;
	game->player.dir.x = -1;
	game->player.dir.y = -1;
}

void	start_game(t_game *game)
{
	start_player(game);
	//game->time = get_ticks();
	//game->old_time = get_ticks();
}
