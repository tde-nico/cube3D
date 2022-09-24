/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_read.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tde-nico <tde-nico@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 11:27:39 by tde-nico          #+#    #+#             */
/*   Updated: 2022/09/21 10:36:24 by tde-nico         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	split_textures(char **file, t_map *map)
{
	int		i;
	int		j;

	i = -1;
	map->search_start = 0;
	while (file[++i])
	{
		j = 2;
		while (file[i] && file[i][0] && file[i][j] == ' ')
			j++;
		if (extra_texture_check(file, map, i, j))
			return (1);
	}
	if (!map->nord || !map->sud || !map->west || !map->east)
		return (free_map_textures(map));
	return (0);
}

int	split_colors(char **file, t_map *map, int i, char **tmp)
{
	while (file[++i])
	{
		if (ft_strnstr(file[i], FLOOR_COLOR, 2))
		{
			if (map->floor)
				return (1);
			tmp = ft_split(&file[i][2], ',');
			if (!(tmp[0] && tmp[1] && tmp[2] && tmp[3] == NULL))
				return (free_matrix(tmp));
			map->floor_color[0] = ft_atoi(tmp[0]);
			map->floor_color[1] = ft_atoi(tmp[1]);
			map->floor_color[2] = ft_atoi(tmp[2]);
			free_matrix(tmp);
			if (i >= map->search_start)
				map->search_start = i + 1;
			map->floor = 1;
		}
		else if (ft_strnstr(file[i], CEILLING_COLOR, 2))
		{
			if (map_add_ceiling(file, map, i, tmp))
				return (1);
		}
	}
	return (0);
}

void	get_map_size(t_map *map, char **file)
{
	int	x;
	int	y;

	while (file[map->search_start] && !file[map->search_start][0])
		++(map->search_start);
	map->map = ft_arrdup(&file[map->search_start]);
	map->width = -1;
	y = -1;
	while (map->map[++y])
	{
		if (map->map[y][0] == 0)
			map->height -= 1;
		x = 0;
		while (map->map[y][x])
			++x;
		if (map->width < x)
			map->width = x;
	}
	map->height += y;
}

void	init_map(t_map *map)
{
	map->search_start = 0;
	map->nord = NULL;
	map->sud = NULL;
	map->west = NULL;
	map->east = NULL;
	map->floor_color[0] = -1;
	map->ceilling_color[0] = -1;
	map->player_pos.x = 0;
	map->player_pos.y = 0;
	map->map = NULL;
	map->width = 0;
	map->height = 0;
	map->floor = 0;
	map->ceilling = 0;
}

t_map	*read_map(char *fname)
{
	t_map	*map;
	char	**file;

	file = read_file(fname);
	map = malloc(sizeof(t_map) * 1);
	if (!map)
		return (map_error(NULL, file, "Error\nMalloc error\n"));
	init_map(map);
	if (split_textures(file, map))
		return (map_error(map, file, "Error\nMissing or too many textures\n"));
	if (split_colors(file, map, -1, NULL))
		return (map_error(map, file, "Error\nInvalid colors format\n"));
	get_map_size(map, file);
	if (!ft_strncmp(VERBOSE, "map_init", 8))
		print_map(map);
	if (validate_map(map, file))
		return (map_error(map, file, NULL));
	free_matrix(file);
	return (map);
}
