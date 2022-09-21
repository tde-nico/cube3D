/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tde-nico <tde-nico@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/08 11:35:00 by tde-nico          #+#    #+#             */
/*   Updated: 2022/09/08 12:47:19 by tde-nico         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_line(t_game *game, t_vec2 begin, t_vec2 end, int color)
{
	double	dx;
	double	dy;
	double	px;
	double	py;
	int		pixels;

	dx = end.x - (int)begin.x;
	dy = end.y - (int)begin.y;
	//printf("x: %f %f\n", dx, dy);
	pixels = sqrt((dx * dx) + (dy * dy));
	dx /= pixels;
	dy /= pixels;
	px = (int)begin.x;
	py = (int)begin.y;
	while (pixels)
	{
		mlx_pixel_put(game->mlx, game->win, px, py, color);
		px += dx;
		py += dy;
		--pixels;
	}
	//printf("x: %f %d %f %f\n", px, pixels, dx, dy);
}

int	update(t_game *game)
{
	int		x;

	mlx_clear_window(game->mlx, game->win);
	x = -1;
	while (++x < WIDTH)
	{
		game->ray.camera_x = 2.0 * (double)x / (double)WIDTH - 1;
		game->ray.ray_dir.x = game->player.dir.x
			+ game->player.plane.x * game->ray.camera_x;
		//printf("++++++++++ %f %f %f \n", game->player.dir.x, game->player.plane.x, game->ray.camera_x);
		game->ray.ray_dir.y = game->player.dir.y
			+ game->player.plane.y * game->ray.camera_x;
		game->ray.map_x = (int)game->player.pos.x;
		game->ray.map_y = (int)game->player.pos.y;
		//printf(">>>> %d %d %f %f\n", game->ray.map_x, game->ray.map_y, game->player.pos.x, game->player.pos.y);
		game->ray.delta_dist.x = 1e30;
		game->ray.delta_dist.y = 1e30;
		//printf("*** %f %f\n", game->ray.ray_dir.x, game->ray.ray_dir.y);
		if (game->ray.ray_dir.x)
			game->ray.delta_dist.x = fabs(1 / game->ray.ray_dir.x);
		if (game->ray.ray_dir.y)
			game->ray.delta_dist.y = fabs(1 / game->ray.ray_dir.y);
		//printf("*** %f %f\n", game->ray.delta_dist.x, game->ray.delta_dist.y);
		game->ray.hit = 0;
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
		//printf(">>>> %d %d\n", game->ray.step_x, game->ray.step_y);
		// DDA
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
			//printf("xy: %d %d\n", game->ray.map_x, game->ray.map_y);
			if (game->map->map[game->ray.map_y][game->ray.map_x] == '1')
				game->ray.hit = 1;
		}
		//printf("|||||| %d %f %f\n", game->ray.side, game->ray.side_dist.y, game->ray.delta_dist.y);
		//printf("|||||| %d %f %f\n", game->ray.side, game->ray.side_dist.x, game->ray.delta_dist.x);
		if (game->ray.side == 0)
			game->ray.perp_wall_dist = (game->ray.side_dist.x
					- game->ray.delta_dist.x);
		else
			game->ray.perp_wall_dist = (game->ray.side_dist.y
					- game->ray.delta_dist.y);
		game->ray.line_height = (int)(HEIGHT / game->ray.perp_wall_dist);
		//printf("||| %f %f\n", HEIGHT / game->ray.perp_wall_dist, game->ray.perp_wall_dist);
		game->ray.draw_start.y = -game->ray.line_height / 2 + HEIGHT / 2;
		if (game->ray.draw_start.y < 0)
			game->ray.draw_start.y = 0;
		game->ray.draw_end.y = game->ray.line_height / 2 + HEIGHT / 2;
		if (game->ray.draw_end.y >= HEIGHT)
			game->ray.draw_end.y = HEIGHT - 1;
		if (game->map->map[game->ray.map_y][game->ray.map_x] == '1')
			game->ray.color = RGB_RED;
		else if (game->map->map[game->ray.map_y][game->ray.map_x] == '2')
			game->ray.color = RGB_GREEN;
		else if (game->map->map[game->ray.map_y][game->ray.map_x] == '3')
			game->ray.color = RGB_BLUE;
		else if (game->map->map[game->ray.map_y][game->ray.map_x] == '4')
			game->ray.color = RGB_WHITE;
		else
			game->ray.color = RGB_YELLOW;
		game->ray.draw_start.x = x;
		game->ray.draw_end.x = x;
		//printf("--- %f %f %f %f\n", game->ray.draw_start.x, game->ray.draw_start.y, game->ray.draw_end.x, game->ray.draw_end.y);
		draw_line(game, game->ray.draw_start,
			game->ray.draw_end, game->ray.color);
	}
	/*game->old_time = game->time;
	game->time = get_ticks();
	game->frame_time = (game->time - game->old_time) / 1000.0;
	printf("fps: %lf\n", game->time);
	mlx_string_put(game->mlx, game->win,
		20, 20, -1, ft_itoa((int)(1.0 / game->frame_time)));*/
	//mlx_clear_window(game->mlx, game->win);
	
	game->frame_time = 1.0 / 60.0;
	game->player.mov_speed.x = game->frame_time * PLAYER_SPEED;
	game->player.mov_speed.y = game->frame_time * PLAYER_SPEED;
	game->player.rot_speed = game->frame_time * PLAYER_ROTATION_SPEED;
	if (game->player.mov_dir.x == -1)
	{
		printf("W\n");
		if (game->map->map[(int)(game->player.pos.y)][(int)(game->player.pos.x
			+ game->player.dir.x * game->player.mov_speed.x)] == '0')
			game->player.pos.x += game->player.dir.x * game->player.mov_speed.x;
		if (game->map->map[(int)(game->player.pos.y + game->player.dir.y
				* game->player.mov_speed.x)][(int)(game->player.pos.x)] == '0')
			game->player.pos.y += game->player.dir.y * game->player.mov_speed.x;
	}
	if (game->player.mov_dir.x == 1)
	{
		printf("S\n");
		if (game->map->map[(int)(game->player.pos.y)][(int)(game->player.pos.x
			- game->player.dir.x * game->player.mov_speed.x)] == '0')
			game->player.pos.x -= game->player.dir.x * game->player.mov_speed.x;
		if (game->map->map[(int)(game->player.pos.y - game->player.dir.y
				* game->player.mov_speed.x)][(int)(game->player.pos.x)] == '0')
			game->player.pos.y -= game->player.dir.y * game->player.mov_speed.x;
	}
	if (game->player.rot_dir == 1)
	{
		printf("D\n");
		double old_dir_x = game->player.dir.x;
		game->player.dir.x = game->player.dir.x * cos(-game->player.rot_speed) - game->player.dir.y * sin(-game->player.rot_speed);
		game->player.dir.y = old_dir_x * sin(-game->player.rot_speed) + game->player.dir.y * cos(-game->player.rot_speed);
		double old_plane_x = game->player.plane.x;
		game->player.plane.x = game->player.plane.x * cos(-game->player.rot_speed) - game->player.plane.y * sin(-game->player.rot_speed);
		game->player.plane.y = old_plane_x * sin(-game->player.rot_speed) + game->player.plane.y * cos(-game->player.rot_speed);
	}
	if (game->player.rot_dir == -1)
	{
		printf("A\n");
		double old_dir_x = game->player.dir.x;
		game->player.dir.x = game->player.dir.x * cos(game->player.rot_speed) - game->player.dir.y * sin(game->player.rot_speed);
		game->player.dir.y = old_dir_x * sin(game->player.rot_speed) + game->player.dir.y * cos(game->player.rot_speed);
		double old_plane_x = game->player.plane.x;
		game->player.plane.x = game->player.plane.x * cos(game->player.rot_speed) - game->player.plane.y * sin(game->player.rot_speed);
		game->player.plane.y = old_plane_x * sin(game->player.rot_speed) + game->player.plane.y * cos(game->player.rot_speed);
	}
	return (0);
}
