/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args_check.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tde-nico <tde-nico@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 11:55:01 by tde-nico          #+#    #+#             */
/*   Updated: 2022/09/07 11:25:21 by tde-nico         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	is_cub(char *str)
{
	int	i;

	i = ft_strlen(str) - 4;
	if (ft_strncmp(&str[i], ".cub", 4))
		return (0);
	return (1);
}

int	check_args(int argc, char **argv)
{
	if (argc < 2)
		return (ft_printf("ERROR: No argument\n"));
	else if (argc > 2)
		return (ft_printf("ERROR: Too many arguments\n"));
	else if (!is_cub(argv[1]))
		return (ft_printf("ERROR: The argument must be .cub\n"));
	return (0);
}
