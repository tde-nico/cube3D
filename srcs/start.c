/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tde-nico <tde-nico@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/08 09:36:45 by tde-nico          #+#    #+#             */
/*   Updated: 2022/09/20 12:21:52 by tde-nico         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
	TEST
nord	0	-1	-fov	0
sud		0	1	fov		0
west	1	0	0		-fov
east	-1	0	0		fov

	REAL
nord	0	-1	fov		0
sud		0	1	-fov	0
west	-1	0	0		-fov
east	1	0	0		fov
*/

void	set_player_view(t_game *game)
{
	char	dir;

	dir = game->map->map[(int)game->map->player_pos.y][
		(int)game->map->player_pos.x];
	if (dir == PLAYER_CHARACTERS[0])
	{
		game->player.dir.y = -1.0;
		game->player.plane.x = PLAYER_FOV;
	}
	else if (dir == PLAYER_CHARACTERS[1])
	{
		game->player.dir.y = 1.0;
		game->player.plane.x = -PLAYER_FOV;
	}
	else if (dir == PLAYER_CHARACTERS[2])
	{
		game->player.dir.x = -1.0;
		game->player.plane.y = -PLAYER_FOV;
	}
	else if (dir == PLAYER_CHARACTERS[3])
	{
		game->player.dir.x = 1.0;
		game->player.plane.y = PLAYER_FOV;
	}
}

void	fix_player_pos(t_game *game)
{
	int	y;
	int	x;

	y = -1;
	while (game->map->map[++y])
	{
		x = -1;
		while (game->map->map[y][++x])
		{
			if (ft_strchr(PLAYER_CHARACTERS, game->map->map[y][x]))
			{
				game->map->map[y][x] = '0';
			}
		}
	}
}

void	start_player(t_game *game)
{
	find_player_pos(game->map);
	game->player.pos.x = (int)game->map->player_pos.x;
	game->player.pos.y = (int)game->map->player_pos.y;
	game->player.dir.x = 0.0;
	game->player.dir.y = 0.0;
	game->player.plane.x = 0.0;
	game->player.plane.y = 0.0;
	game->player.mov_dir.x = 0;
	game->player.mov_dir.y = 0;
	game->player.rot_dir = 0;
	set_player_view(game);
	fix_player_pos(game);
}

void	start_game(t_game *game)
{
	start_player(game);
	game->time = get_time();
	game->old_time = get_time();
	game->mouse_prev_x = WIDTH / 2;
	game->door_frame = 0;
}
