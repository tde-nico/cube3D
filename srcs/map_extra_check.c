/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_extra_check.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tde-nico <tde-nico@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 09:31:03 by tde-nico          #+#    #+#             */
/*   Updated: 2022/09/21 10:37:14 by tde-nico         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	map_add_ceiling(char **file, t_map *map, int i, char **tmp)
{
	if (map->ceilling)
		return (1);
	tmp = ft_split(&file[i][2], ',');
	if (!(tmp[0] && tmp[1] && tmp[2] && tmp[3] == NULL))
		return (free_matrix(tmp));
	map->ceilling_color[0] = ft_atoi(tmp[0]);
	map->ceilling_color[1] = ft_atoi(tmp[1]);
	map->ceilling_color[2] = ft_atoi(tmp[2]);
	free_matrix(tmp);
	if (i >= map->search_start)
		map->search_start = i + 1;
	map->ceilling = 1;
	return (0);
}

int	extra_texture_half(char **file, t_map *map, int i, int j)
{
	if (ft_strnstr(file[i], WEST_TEXTURE, 3))
	{
		if (map->west)
			return (1);
		map->west = ft_strdup(&file[i][j]);
		map->search_start = i + 1;
	}
	else if (ft_strnstr(file[i], EAST_TEXTURE, 3))
	{
		if (map->east)
			return (1);
		map->east = ft_strdup(&file[i][j]);
		map->search_start = i + 1;
	}
	return (0);
}

int	extra_texture_check(char **file, t_map *map, int i, int j)
{
	if (ft_strnstr(file[i], NORD_TEXTURE, 3))
	{
		if (map->nord)
			return (1);
		map->nord = ft_strdup(&file[i][j]);
		map->search_start = i + 1;
	}
	else if (ft_strnstr(file[i], SUD_TEXTURE, 3))
	{
		if (map->sud)
			return (1);
		map->sud = ft_strdup(&file[i][j]);
		map->search_start = i + 1;
	}
	else if (ft_strnstr(file[i], WEST_TEXTURE, 3)
		|| ft_strnstr(file[i], EAST_TEXTURE, 3))
	{
		if (extra_texture_half(file, map, i, j))
			return (1);
	}
	return (0);
}

int	check_keys(t_map *map, char **file)
{
	int	i;

	i = -1;
	while (file[++i])
	{
		if (i >= map->search_start && i <= (map->search_start + map->height))
			continue ;
		if (!(ft_strnstr(file[i], NORD_TEXTURE, 3)
				|| ft_strnstr(file[i], SUD_TEXTURE, 3)
				|| ft_strnstr(file[i], WEST_TEXTURE, 3)
				|| ft_strnstr(file[i], EAST_TEXTURE, 3)
				|| ft_strnstr(file[i], FLOOR_COLOR, 2)
				|| ft_strnstr(file[i], CEILLING_COLOR, 2)
				|| file[i][0] == 0))
		{
			return (1);
		}
	}
	return (0);
}

int	map_extra_check(t_map *map, char **file)
{
	if (check_keys(map, file))
		return (ft_printf("Error\nInvalid Key\n"));
	return (0);
}
