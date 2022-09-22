/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tde-nico <tde-nico@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 10:47:07 by tde-nico          #+#    #+#             */
/*   Updated: 2022/09/19 11:16:12 by tde-nico         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_minimap_back_and_player(t_game *game)
{
	t_vec2	begin;
	t_vec2	end;

	begin.x = 0;
	begin.y = 0;
	end.x = game->mini.width;
	end.y = game->mini.height;
	draw_rect_on(&game->mini.map, begin, end, RGB_DARK_GREY);
	begin.x = (int)(game->player.pos.x * MINIMAP_TILE_SIZE) - 1;
	begin.y = (int)(game->player.pos.y * MINIMAP_TILE_SIZE) - 2;
	end.x = (int)(game->player.pos.x * MINIMAP_TILE_SIZE) + 2;
	end.y = (int)(game->player.pos.y * MINIMAP_TILE_SIZE) + 2;
	draw_rect_on(&game->mini.map, begin, end, RGB_RED);
}

void	draw_minimap_walls(t_game *game)
{
	t_vec2	begin;
	t_vec2	end;
	int		x;
	int		y;

	y = -1;
	while (game->map->map[++y])
	{
		x = -1;
		while (game->map->map[y][++x])
		{
			if (game->map->map[y][x] == '1')
			{
				begin.x = x * MINIMAP_TILE_SIZE;
				begin.y = y * MINIMAP_TILE_SIZE;
				end.x = begin.x + MINIMAP_TILE_SIZE;
				end.y = begin.y + MINIMAP_TILE_SIZE;
				draw_empty_rect_on(&game->mini.map, begin, end, RGB_GREEN);
			}
		}
	}
}

void	draw_minimap_doors(t_game *game)
{
	t_vec2	begin;
	t_vec2	end;
	int		x;
	int		y;

	y = -1;
	while (game->map->map[++y])
	{
		x = -1;
		while (game->map->map[y][++x])
		{
			if (ft_strchr("DO", game->map->map[y][x]))
			{
				begin.x = x * MINIMAP_TILE_SIZE;
				begin.y = y * MINIMAP_TILE_SIZE;
				end.x = begin.x + MINIMAP_TILE_SIZE;
				end.y = begin.y + MINIMAP_TILE_SIZE;
				if (game->map->map[y][x] == 'D')
					draw_empty_rect_on(&game->mini.map, begin, end, RGB_RED);
				else
					draw_empty_rect_on(&game->mini.map, begin, end, RGB_YELLOW);
			}
		}
	}
}

void	draw_minimap(t_game *game)
{
	draw_minimap_back_and_player(game);
	draw_minimap_walls(game);
	draw_minimap_doors(game);
	game->mini.begin_ray.x = game->player.pos.x * MINIMAP_TILE_SIZE;
	game->mini.begin_ray.y = game->player.pos.y * MINIMAP_TILE_SIZE;
}

void	draw_minimap_rays(t_game *game)
{
	game->mini.end_ray.x = (game->ray.ray_dir.x * game->ray.perp_wall_dist
			+ game->player.pos.x) * (double)MINIMAP_TILE_SIZE;
	game->mini.end_ray.y = (game->ray.ray_dir.y * game->ray.perp_wall_dist
			+ game->player.pos.y) * (double)MINIMAP_TILE_SIZE;
	draw_line_on(&game->mini.map, game->mini.begin_ray, game->mini.end_ray,
		RGB_WHITE);
}
