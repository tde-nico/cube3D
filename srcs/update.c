/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tde-nico <tde-nico@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/08 11:35:00 by tde-nico          #+#    #+#             */
/*   Updated: 2022/09/21 09:19:49 by tde-nico         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_background(t_game *game)
{
	t_vec2	begin;
	t_vec2	end;
	int		y;

	begin.x = 0;
	end.x = WIDTH;
	y = -1;
	while (++y < (HEIGHT / 2))
	{
		begin.y = y;
		end.y = y;
		draw_line_on(&game->screen, begin, end, create_trgb(0,
				game->map->ceilling_color[0], game->map->ceilling_color[1],
				game->map->ceilling_color[2]));
	}
	y -= 1;
	while (++y < HEIGHT)
	{
		begin.y = y;
		end.y = y;
		draw_line_on(&game->screen, begin, end, create_trgb(0,
				game->map->floor_color[0], game->map->floor_color[1],
				game->map->floor_color[2]));
	}
}

void	update_time(t_game *game)
{
	char	*curr_fps;

	game->old_time = game->time;
	game->time = get_time();
	game->frame_time = (game->time - game->old_time) / 1000.0;
	game->fps = (int)(1.0 / game->frame_time);
	if (game->fps > FPS_LOCK)
	{
		ft_sleep(((1.0 / FPS_LOCK) - game->frame_time) * 1000);
		game->time = get_time();
		game->frame_time = (game->time - game->old_time) / 1000.0;
		game->fps = (int)(1.0 / game->frame_time);
	}
	curr_fps = ft_itoa(game->fps);
	mlx_string_put(game->mlx, game->win,
		20, 20, -1, curr_fps);
	free(curr_fps);
	game->door_frame += 1;
}

int	check_door_proximity(t_game *game)
{
	int		x;
	int		y;

	y = -1;
	while (game->map->map[++y])
	{
		x = -1;
		while (game->map->map[y][++x])
		{
			if (ft_strchr("D", game->map->map[y][x]) && (sqrtf(powf(x
				- game->player.pos.x, 2.0) + powf(y
				- game->player.pos.y, 2.0))) < DOOR_DIST)
				game->map->map[y][x] = 'O';
			else if (ft_strchr("O", game->map->map[y][x]) && (sqrtf(powf(x
				- game->player.pos.x, 2.0) + powf(y
				- game->player.pos.y, 2.0))) > DOOR_DIST)
				game->map->map[y][x] = 'D';
		}
	}
	return (0);
}

int	update(t_game *game)
{
	mlx_clear_window(game->mlx, game->win);
	draw_minimap(game);
	draw_background(game);
	raycaster_flat(game);
	mlx_put_image_to_window(game->mlx, game->win, game->screen.img, 0, 0);
	mlx_put_image_to_window(game->mlx, game->win, game->mini.map.img,
		game->mini.x, game->mini.y);
	update_time(game);
	update_inputs(game);
	check_door_proximity(game);
	return (0);
}
