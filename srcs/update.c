/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tde-nico <tde-nico@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/08 11:35:00 by tde-nico          #+#    #+#             */
/*   Updated: 2022/09/13 13:02:16 by tde-nico         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
}

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

int	update(t_game *game)
{
	mlx_clear_window(game->mlx, game->win);
	draw_background(game);
	raycaster_flat(game);
	mlx_put_image_to_window(game->mlx, game->win, game->screen.img, 0, 0);
	update_time(game);
	update_inputs(game);
	return (0);
}
