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

char	*get_next_line(int fd)
{
	int		byte;
	char	buffer;
	char	*line;

	byte = 1;
	line = ft_calloc(1, sizeof(char));
	while (byte)
	{
		byte = read(fd, &buffer, 1);
		if (buffer == '\n' || !byte)
		{
			if (!byte)
				free(line);
			break ;
		}
		line = ft_charjoin(line, buffer);
	}
	return (line);
}
