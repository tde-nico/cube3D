/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tde-nico <tde-nico@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 11:27:39 by tde-nico          #+#    #+#             */
/*   Updated: 2022/09/16 11:25:43 by tde-nico         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
	DOCS
MLX		https://harm-smits.github.io/42docs/libs/minilibx/getting_started.html
CUB3D	https://harm-smits.github.io/42docs/projects/cub3d
LINE	https://gontjarow.github.io/MiniLibX/mlx-tutorial-draw-line.html

FIND	https://find-peers.codam.nl/Rome

*/

int	clean_exit(t_game *game)
{
	mlx_clear_window(game->mlx, game->win);
	mlx_destroy_window(game->mlx, game->win);
	free_game(game);
	exit(0);
	return (0);
}

int	exit_game(void)
{
	exit(0);
	return (0);
}

int	main(int argc, char **argv)
{
	t_game	game;

	if (check_args(argc, argv))
		return (1);
	game.map = read_map(argv[1]);
	if (!game.map)
		return (!INVALID_TESTING);
	start_game(&game);
	init_game(&game);
	mlx_hook(game.win, ON_KEYDOWN, 1L << 0, input_handler_down, (void *)&game);
	mlx_hook(game.win, ON_KEYUP, 1L << 1, input_handler_up, (void *)&game);
	mlx_hook(game.win, ON_MOUSEMOVE, 1L << 6, mouse_handler, (void *)&game);
	mlx_hook(game.win, ON_DESTROY, 0, clean_exit, (void *)&game);
	mlx_loop_hook(game.mlx, update, (void *)&game);
	mlx_loop(game.mlx);
	return (0);
}
