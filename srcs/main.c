/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tde-nico <tde-nico@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 11:27:39 by tde-nico          #+#    #+#             */
/*   Updated: 2022/09/06 12:56:43 by tde-nico         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(int argc, char **argv)
{
	t_game	game;
	int		i;

	if (check_args(argc, argv))
		return (1);
	game.map = read_map(argv[1]);
	if (!game.map)
		return (free_matrix(game.map));
	i = -1;
	while (game.map[++i])
		ft_printf("%s\n", game.map[i]);
	free_matrix(game.map);
	return (0);
}
