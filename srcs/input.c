/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tde-nico <tde-nico@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/08 08:39:09 by tde-nico          #+#    #+#             */
/*   Updated: 2022/09/16 12:23:08 by tde-nico         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	input_handler_down(int key, t_game *game)
{
	(void)game;
	if (!ft_strncmp(VERBOSE, "inputs", 6))
		ft_printf("key down: %d\n", key);
	if (key == K_W || key == LK_W)
		game->player.mov_dir.x = -1;
	else if (key == K_S || key == LK_S)
		game->player.mov_dir.x = 1;
	else if (key == K_A || key == LK_A)
		game->player.mov_dir.y = -1;
	else if (key == K_D || key == LK_D)
		game->player.mov_dir.y = 1;
	else if (key == K_LEFT || key == LK_LEFT)
		game->player.rot_dir = -1;
	else if (key == K_RIGHT || key == LK_RIGHT)
		game->player.rot_dir = 1;
	else if (key == K_ESCAPE || key == LK_ESCAPE)
		clean_exit(game);
	return (0);
}

int	input_handler_up(int key, t_game *game)
{
	(void)game;
	if (!ft_strncmp(VERBOSE, "inputs", 6))
		ft_printf("key up: %d\n", key);
	if (key == K_W || key == K_S || key == LK_W || key == LK_S)
		game->player.mov_dir.x = 0;
	else if (key == K_A || key == K_D || key == LK_A || key == LK_D)
		game->player.mov_dir.y = 0;
	else if (key == K_LEFT || key == K_RIGHT
		|| key == LK_LEFT || key == LK_RIGHT)
		game->player.rot_dir = 0;
	return (0);
}

int	mouse_handler(int x, int y, t_game *game)
{
	if (x < 0 || x > WIDTH || y < 0 || y > HEIGHT)
		return (0);
	if (!ft_strncmp(VERBOSE, "inputs", 6))
		ft_printf("Mouse on x: %d y: %d\n", x, y);
	if (x > game->mouse_prev_x)
		game->player.rot_dir = 1;
	else if (x < game->mouse_prev_x)
		game->player.rot_dir = -1;
	game->player.rot_speed = game->frame_time * PLAYER_ROTATION_SPEED * 1.2;
	update_rot(game);
	game->player.rot_dir = 0;
	game->mouse_prev_x = x;
	return (0);
}
