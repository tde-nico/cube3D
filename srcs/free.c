/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tde-nico <tde-nico@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 11:27:39 by tde-nico          #+#    #+#             */
/*   Updated: 2022/09/19 11:34:53 by tde-nico         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	free_matrix(char **matrix)
{
	int	i;

	i = -1;
	if (!matrix)
		return (1);
	while (matrix[++i])
		free(matrix[i]);
	free(matrix);
	return (1);
}

int	free_map_textures(t_map *map)
{
	if (map->nord)
	{
		free(map->nord);
		map->nord = NULL;
	}
	if (map->sud)
	{
		free(map->sud);
		map->sud = NULL;
	}
	if (map->west)
	{
		free(map->west);
		map->west = NULL;
	}
	if (map->east)
	{
		free(map->east);
		map->east = NULL;
	}
	return (1);
}

int	free_map(t_map *map)
{
	if (!map)
		return (1);
	free_map_textures(map);
	free_matrix(map->map);
	free(map);
	map = NULL;
	return (1);
}

int	free_images(t_game *game)
{
	if (game->screen.img)
		mlx_destroy_image(game->mlx, game->screen.img);
	if (game->walls[0].img)
		mlx_destroy_image(game->mlx, game->walls[0].img);
	if (game->walls[1].img)
		mlx_destroy_image(game->mlx, game->walls[1].img);
	if (game->walls[2].img)
		mlx_destroy_image(game->mlx, game->walls[2].img);
	if (game->walls[3].img)
		mlx_destroy_image(game->mlx, game->walls[3].img);
	if (game->walls[4].img)
		mlx_destroy_image(game->mlx, game->walls[4].img);
	if (game->mini.map.img)
		mlx_destroy_image(game->mlx, game->mini.map.img);
	return (1);
}

int	free_game(t_game *game)
{
	free_map(game->map);
	free_images(game);
	return (1);
}
