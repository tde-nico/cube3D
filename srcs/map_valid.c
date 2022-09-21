/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_valid.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tde-nico <tde-nico@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 11:27:39 by tde-nico          #+#    #+#             */
/*   Updated: 2022/09/09 17:35:53 by tde-nico         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	path_exist(char *path)
{
	int	fd;

	fd = open(path, O_RDONLY);
	if (fd < 1)
		return (0);
	close(fd);
	return (1);
}

int	verify_map_textures_and_colors(t_map *map)
{
	if (!path_exist(map->nord) || !path_exist(map->sud)
		|| !path_exist(map->west) || !path_exist(map->east))
		return (ft_printf("Error\nInvalid textures\n"));
	if (map->floor_color[0] < 0 || map->floor_color[0] > 255
		|| map->floor_color[1] < 0 || map->floor_color[0] > 255
		|| map->floor_color[2] < 0 || map->floor_color[2] > 255
		|| map->ceilling_color[0] < 0 || map->ceilling_color[0] > 255
		|| map->ceilling_color[1] < 0 || map->ceilling_color[1] > 255
		|| map->ceilling_color[2] < 0 || map->ceilling_color[2] > 255)
		return (ft_printf("Error\nInvalid colors\n"));
	return (0);
}

int	verify_map_integrity(char **map)
{
	size_t	y;
	size_t	x;

	y = -1;
	while (map[++y])
	{
		x = -1;
		while (map[y][++x])
		{
			if (!ft_strchr(MAP_CHARACTERS, map[y][x]))
				return (ft_printf("Error\nWrong characters in map\n"));
			if (MAP_CHARACTERS[1] == map[y][x] && ((!y || !x || !map[y + 1]
				|| (x && (map[y][x - 1] == ' ' || map[y][x - 1] == '\0'))
						|| (x < ft_strlen(map[y]) && (map[y][x + 1] == ' '
							|| map[y][x + 1] == '\0')))
					|| ((y && x < (ft_strlen(map[y - 1]) - 1) && (map[y - 1][x]
						== ' ' || map[y - 1][x] == '\0')) || (map[y + 1]
						&& (x > (ft_strlen(map[y + 1]) - 1) || (map[y + 1][x]
						== ' ' || map[y + 1][x] == '\0'))))))
				return (ft_printf("Error\nMap open at %d %d\n", x, y));
		}
	}
	return (0);
}

int	find_player_pos(t_map *map)
{
	int	y;
	int	x;

	y = -1;
	while (map->map[++y])
	{
		x = -1;
		while (map->map[y][++x])
		{
			if (ft_strchr(PLAYER_CHARACTERS, map->map[y][x]))
			{
				map->player_pos.x = x;
				map->player_pos.y = y;
				return (1);
			}
		}
	}
	return (0);
}

int	validate_map(t_map *map)
{
	if (verify_map_textures_and_colors(map))
		return (1);
	if (verify_map_integrity(map->map))
		return (1);
	if (!find_player_pos(map))
		return (ft_printf("Error\nPlayer not in map\n"));
	return (0);
}
