/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_read.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tde-nico <tde-nico@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 11:27:39 by tde-nico          #+#    #+#             */
/*   Updated: 2022/09/07 11:39:09 by tde-nico         ###   ########.fr       */
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
		if (ft_strnstr(file[i], NORD_TEXTURE, 2))
			map->nord = ft_strdup(&file[i][j]);
		else if (ft_strnstr(file[i], SUD_TEXTURE, 2))
			map->sud = ft_strdup(&file[i][j]);
		else if (ft_strnstr(file[i], WEST_TEXTURE, 2))
			map->west = ft_strdup(&file[i][j]);
		else if (ft_strnstr(file[i], EAST_TEXTURE, 2))
			map->east = ft_strdup(&file[i][j]);
	}
	if (!map->nord || !map->sud || !map->west || !map->east)
		return (free_map_textures(map));
	return (0);
}

int	split_colors(char **file, t_map *map, int i)
{
	char	**tmp;

	tmp = NULL;
	while (file[++i])
	{
		if (ft_strnstr(file[i], FLOOR_COLOR, 1))
		{
			tmp = ft_split(&file[i][2], ',');
			map->floor_color[0] = ft_atoi(tmp[0]);
			map->floor_color[1] = ft_atoi(tmp[1]);
			map->floor_color[2] = ft_atoi(tmp[2]);
			free_matrix(tmp);
			map->search_start = i + 1;
		}
		else if (ft_strnstr(file[i], CEILLING_COLOR, 1))
		{
			tmp = ft_split(&file[i][2], ',');
			map->ceilling_color[0] = ft_atoi(tmp[0]);
			map->ceilling_color[1] = ft_atoi(tmp[1]);
			map->ceilling_color[2] = ft_atoi(tmp[2]);
			free_matrix(tmp);
			map->search_start = i + 1;
		}
	}
	return (0);
}

void	get_map_size(t_map *map)
{
	int	x;
	int	y;

	map->width = -1;
	y = -1;
	while (map->map[++y])
	{
		x = 0;
		while (map->map[y][x])
			++x;
		if (map->width < x)
			map->width = x;
	}
	map->height = y;
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
}

t_map	*read_map(char *fname)
{
	t_map	*map;
	char	**file;

	file = read_file(fname);
	map = malloc(sizeof(t_map) * 1);
	if (!map)
		return (map_error(NULL, file, "ERROR: Malloc error\n"));
	init_map(map);
	if (split_textures(file, map))
		return (map_error(map, file, "ERROR: Missing textures\n"));
	if (split_colors(file, map, -1))
		return (map_error(map, file, "ERROR: Invalid colors format\n"));
	while (file[map->search_start] && !file[map->search_start][0])
		++(map->search_start);
	map->map = ft_arrdup(&file[map->search_start]);
	get_map_size(map);
	if (!ft_strncmp(VERBOSE, "map_init", 8))
		print_map(map);
	if (validate_map(map))
		return (map_error(map, file, NULL));
	free_matrix(file);
	return (map);
}
