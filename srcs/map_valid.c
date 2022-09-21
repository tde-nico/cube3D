/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_valid.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tde-nico <tde-nico@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 11:27:39 by tde-nico          #+#    #+#             */
/*   Updated: 2022/09/07 11:18:09 by tde-nico         ###   ########.fr       */
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

int	verify_map_textures(t_map *map)
{
	if (!path_exist(map->nord) || !path_exist(map->sud)
		|| !path_exist(map->west) || !path_exist(map->east))
		return (0);
	return (1);
}

int	verify_map_colors(t_map *map)
{
	if (map->floor_color[0] < 0 || map->floor_color[0] > 255
		|| map->floor_color[1] < 0 || map->floor_color[0] > 255
		|| map->floor_color[2] < 0 || map->floor_color[2] > 255
		|| map->ceilling_color[0] < 0 || map->ceilling_color[0] > 255
		|| map->ceilling_color[1] < 0 || map->ceilling_color[1] > 255
		|| map->ceilling_color[2] < 0 || map->ceilling_color[2] > 255)
		return (0);
	return (1);
}

int	verify_map_chars(char **map)
{
	int	y;
	int	x;

	y = -1;
	while (map[++y])
	{
		x = -1;
		while (map[y][++x])
		{
			if (!ft_strchr(MAP_CHARACTERS, map[y][x]))
				return (0);
		}
	}
	return (1);
}

int	validate_map(t_map *map)
{
	if (!verify_map_textures(map))
		return (ft_printf("ERROR: Invalid textures\n"));
	if (!verify_map_colors(map))
		return (ft_printf("ERROR: Invalid colors\n"));
	if (!verify_map_chars(map->map))
		return (ft_printf("ERROR: Wrong characters in map\n"));
	return (0);
}
