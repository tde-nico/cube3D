/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tde-nico <tde-nico@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/08 11:35:00 by tde-nico          #+#    #+#             */
/*   Updated: 2022/09/16 13:00:56 by tde-nico         ###   ########.fr       */
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

void	draw_minimap(t_game *game)
{
	t_vec2	begin;
	t_vec2	end;
	int		y;
	int		x;

	begin.x = WIDTH - MINIMAP_TILE_SIZE * (game->map->width + 1);
	begin.y = MINIMAP_TILE_SIZE;
	end.x = WIDTH - MINIMAP_TILE_SIZE;
	end.y = MINIMAP_TILE_SIZE * (game->map->height + 1);
	draw_rect_on(&game->screen, begin, end, RGB_WHITE);
	y = -1;
	while (game->map->map[++y])
	{
		x = -1;
		while (game->map->map[y][++x])
		{
			if (game->map->map[y][x] == '1')
			{
				//ft_printf("wall: %d %d\n", y, x);
				begin.x = (double)(WIDTH + MINIMAP_TILE_SIZE * (-game->map->width - 1 + x));
				begin.y = (double)(MINIMAP_TILE_SIZE * (-game->map->height - 1 + y));
				end.x = begin.x + MINIMAP_TILE_SIZE;
				end.y = begin.y + MINIMAP_TILE_SIZE;
				//printf("%f\n", (double)( y));
				//printf("%f %f %f %f\n", begin.x, begin.y, end.x, end.y);
				draw_empty_rect_on(&game->screen, begin, end, RGB_BLUE);
			}
		}
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
}

int	update(t_game *game)
{
	mlx_clear_window(game->mlx, game->win);
	draw_background(game);
	raycaster_flat(game);
	draw_minimap(game);
	mlx_put_image_to_window(game->mlx, game->win, game->screen.img, 0, 0);
	update_time(game);
	update_inputs(game);
	return (0);
}
