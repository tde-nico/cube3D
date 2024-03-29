/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tde-nico <tde-nico@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 11:44:10 by tde-nico          #+#    #+#             */
/*   Updated: 2022/09/20 12:24:45 by tde-nico         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	get_texture_x(t_game *game)
{
	double	wall_x;
	int		tex_x;

	if (game->ray.side == 0)
		wall_x = game->player.pos.y + game->ray.perp_wall_dist
			* game->ray.ray_dir.y;
	else
		wall_x = game->player.pos.x + game->ray.perp_wall_dist
			* game->ray.ray_dir.x;
	wall_x -= (int)(wall_x);
	tex_x = (int)(wall_x * (double)(TEXTURE_SIZE));
	if (game->ray.side == 0 && game->ray.ray_dir.x > 0)
		tex_x = TEXTURE_SIZE - tex_x - 1;
	if (game->ray.side == 1 && game->ray.ray_dir.y < 0)
		tex_x = TEXTURE_SIZE - tex_x - 1;
	return (tex_x);
}

void	render_texture(t_game *game, int x)
{
	t_vec2			tex;
	double			step;
	double			tex_pos;
	int				y;
	unsigned int	color;

	tex.x = get_texture_x(game);
	step = 1.0 * TEXTURE_SIZE / game->ray.line_height;
	tex_pos = (game->ray.draw_start.y - HEIGHT / 2 + game->ray.line_height / 2)
		* step;
	y = game->ray.draw_start.y - 1;
	while (++y < game->ray.draw_end.y)
	{
		tex.y = (int)tex_pos & (TEXTURE_SIZE - 1);
		tex_pos += step;
		color = *(unsigned int *)(game->walls[game->ray.color].addr
				+ 4 * (TEXTURE_SIZE * (int)tex.y + (int)tex.x));
		my_mlx_pixel_put(&game->screen, x, y, color);
	}
}

void	select_texture(t_game *game)
{
	if (game->map->map[game->ray.map_y][game->ray.map_x] == 'D')
	{
		if (game->door_frame < (DOOR_FRAMES * 14))
			game->ray.color = 4;
		else if (game->door_frame < (DOOR_FRAMES * 23))
			game->ray.color = (game->door_frame / DOOR_FRAMES) - 10;
		else
		{
			game->ray.color = 4;
			game->door_frame = 0;
		}
	}
	else if (game->ray.side == 1 && game->player.pos.y <= game->ray.map_y)
		game->ray.color = 1;
	else if (game->ray.side == 1)
		game->ray.color = 0;
	else if (game->ray.side == 0 && game->player.pos.x <= game->ray.map_x)
		game->ray.color = 2;
	else if (game->ray.side == 0)
		game->ray.color = 3;
	else
		game->ray.color = 0;
}

void	draw_texture(t_game *game, int x)
{
	int	colors[4];

	select_texture(game);
	if (TEXTURE_MODE)
		render_texture(game, x);
	else
	{
		colors[0] = RGB_BLUE;
		colors[1] = RGB_GREEN;
		colors[2] = RGB_RED;
		colors[3] = RGB_YELLOW;
		game->ray.color %= 4;
		draw_line_on(&game->screen, game->ray.draw_start,
			game->ray.draw_end, colors[game->ray.color]);
	}
}
