/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_images.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tde-nico <tde-nico@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 11:27:39 by tde-nico          #+#    #+#             */
/*   Updated: 2022/09/07 13:01:02 by tde-nico         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	my_mlx_pixel_put(t_minimap *minimap, int x, int y, int color)
{
	char	*dst;

	dst = minimap->addr
		+ (y * minimap->line_length + x * (minimap->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void	draw_line(t_game *game, t_vec2 begin, t_vec2 end, int color)
{
	double	dx;
	double	dy;
	double	px;
	double	py;
	int		pixels;

	dx = end.x - begin.x;
	dy = end.y - begin.y;
	pixels = sqrt((dx * dx) + (dy * dy));
	dx /= pixels;
	dy /= pixels;
	px = begin.x;
	py = begin.y;
	while (pixels)
	{
		mlx_pixel_put(game->mlx, game->win, px, py, color);
		px += dx;
		py += dy;
		--pixels;
	}
}
