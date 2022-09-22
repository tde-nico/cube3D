/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_draw.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tde-nico <tde-nico@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 10:54:15 by tde-nico          #+#    #+#             */
/*   Updated: 2022/09/16 12:39:58 by tde-nico         ###   ########.fr       */
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
}

void	my_mlx_pixel_put(t_image *img, int x, int y, int color)
{
	char	*dst;

	dst = img->addr
		+ (y * img->line_length + x * (img->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void	draw_line_on(t_image *img, t_vec2 begin, t_vec2 end, int color)
{
	double	dx;
	double	dy;
	double	px;
	double	py;
	int		pixels;

	dx = end.x - (int)begin.x;
	dy = end.y - (int)begin.y;
	pixels = sqrt((dx * dx) + (dy * dy));
	dx /= pixels;
	dy /= pixels;
	px = (int)begin.x;
	py = (int)begin.y;
	while (pixels)
	{
		my_mlx_pixel_put(img, px, py, color);
		px += dx;
		py += dy;
		--pixels;
	}
}

void	draw_rect_on(t_image *img, t_vec2 begin, t_vec2 end, int color)
{
	t_vec2	tmp;

	tmp.x = end.x;
	tmp.y = begin.y - 1;
	while (++tmp.y < (end.y + 1))
	{
		draw_line_on(img, begin, tmp, color);
		++begin.y;
	}
}

void	draw_empty_rect_on(t_image *img, t_vec2 begin, t_vec2 end, int color)
{
	t_vec2	tmp;

	tmp.x = begin.x;
	tmp.y = end.y;
	draw_line_on(img, begin, tmp, color);
	draw_line_on(img, tmp, end, color);
	tmp.x = end.x;
	tmp.y = begin.y;
	draw_line_on(img, begin, tmp, color);
	draw_line_on(img, tmp, end, color);
}
