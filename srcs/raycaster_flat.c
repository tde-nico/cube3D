/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster_flat.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tde-nico <tde-nico@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 10:39:22 by tde-nico          #+#    #+#             */
/*   Updated: 2022/09/16 11:55:13 by tde-nico         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_raycast(t_game *game, int x)
{
	game->ray.camera_x = 2.0 * (double)x / (double)WIDTH - 1;
	game->ray.ray_dir.x = game->player.dir.x
		+ game->player.plane.x * game->ray.camera_x;
	game->ray.ray_dir.y = game->player.dir.y
		+ game->player.plane.y * game->ray.camera_x;
	game->ray.map_x = (int)game->player.pos.x;
	game->ray.map_y = (int)game->player.pos.y;
	game->ray.delta_dist.x = 1e30;
	game->ray.delta_dist.y = 1e30;
	if (game->ray.ray_dir.x)
		game->ray.delta_dist.x = fabs(1 / game->ray.ray_dir.x);
	if (game->ray.ray_dir.y)
		game->ray.delta_dist.y = fabs(1 / game->ray.ray_dir.y);
	game->ray.hit = 0;
	game->ray.draw_start.x = x;
	game->ray.draw_end.x = x;
}

void	calculate_side_dist_and_step(t_game *game)
{
	if (game->ray.ray_dir.x < 0)
	{
		game->ray.step_x = -1;
		game->ray.side_dist.x = (game->player.pos.x - game->ray.map_x)
			* game->ray.delta_dist.x;
	}
	else
	{
		game->ray.step_x = 1;
		game->ray.side_dist.x = (game->ray.map_x + 1.0 - game->player.pos.x)
			* game->ray.delta_dist.x;
	}
	if (game->ray.ray_dir.y < 0)
	{
		game->ray.step_y = -1;
		game->ray.side_dist.y = (game->player.pos.y - game->ray.map_y)
			* game->ray.delta_dist.y;
	}
	else
	{
		game->ray.step_y = 1;
		game->ray.side_dist.y = (game->ray.map_y + 1.0 - game->player.pos.y)
			* game->ray.delta_dist.y;
	}
}

void	perform_dda(t_game *game)
{
	while (game->ray.hit == 0)
	{
		if (game->ray.side_dist.x < game->ray.side_dist.y)
		{
			game->ray.side_dist.x += game->ray.delta_dist.x;
			game->ray.map_x += game->ray.step_x;
			game->ray.side = 0;
		}
		else
		{
			game->ray.side_dist.y += game->ray.delta_dist.y;
			game->ray.map_y += game->ray.step_y;
			game->ray.side = 1;
		}
		if (game->map->map[game->ray.map_y][game->ray.map_x] == '1')
			game->ray.hit = 1;
	}
}

void	get_line_size(t_game *game)
{
	if (game->ray.side == 0)
		game->ray.perp_wall_dist = (game->ray.side_dist.x
				- game->ray.delta_dist.x);
	else
		game->ray.perp_wall_dist = (game->ray.side_dist.y
				- game->ray.delta_dist.y);
	game->ray.line_height = (int)(HEIGHT / game->ray.perp_wall_dist);
	game->ray.draw_start.y = -game->ray.line_height / 2 + HEIGHT / 2;
	if (game->ray.draw_start.y < 0)
		game->ray.draw_start.y = 0;
	game->ray.draw_end.y = game->ray.line_height / 2 + HEIGHT / 2;
	if (game->ray.draw_end.y >= HEIGHT)
		game->ray.draw_end.y = HEIGHT - 1;
}

void	raycaster_flat(t_game *game)
{
	int		x;

	x = -1;
	while (++x < WIDTH)
	{
		init_raycast(game, x);
		calculate_side_dist_and_step(game);
		perform_dda(game);
		get_line_size(game);
		draw_texture(game, x);
	}
}
