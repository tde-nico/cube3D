/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tde-nico <tde-nico@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 09:18:49 by tde-nico          #+#    #+#             */
/*   Updated: 2022/09/07 11:37:42 by tde-nico         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	print_matrix(char **matrix)
{
	size_t	i;
	size_t	len;

	if (!matrix)
		return ;
	if (!matrix[0])
		return ;
	len = ft_strlen(matrix[0]) * 2;
	i = -1;
	while (++i < len)
		ft_printf("-");
	ft_printf("\n");
	i = -1;
	while (matrix[++i])
		ft_printf("%s\n", matrix[i]);
	i = -1;
	while (++i < len)
		ft_printf("-");
	ft_printf("\n");
}

void	print_map(t_map *map)
{
	ft_printf("%s\n", map->nord);
	ft_printf("%s\n", map->sud);
	ft_printf("%s\n", map->west);
	ft_printf("%s\n\n", map->east);
	ft_printf("F %d ", map->floor_color[0]);
	ft_printf("%d %d\n", map->floor_color[1], map->floor_color[2]);
	ft_printf("C %d ", map->ceilling_color[0]);
	ft_printf("%d %d\n", map->ceilling_color[1], map->ceilling_color[2]);
	print_matrix(map->map);
	ft_printf("%d %d\n", map->width, map->height);
}
