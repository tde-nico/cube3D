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

int	count_lines(char *file)
{
	int		lines;
	int		fd;
	int		bytes;
	char	buffer;

	fd = open(file, O_RDONLY);
	if (!fd)
		return (-1);
	lines = 1;
	bytes = read(fd, &buffer, 1);
	while (bytes > 0)
	{
		if (buffer == '\n')
			lines++;
		bytes = read(fd, &buffer, 1);
	}
	close(fd);
	return (lines);
}

char	**read_map(char *fname)
{
	char	**map;
	int		fd;
	int		line;
	int		lines;

	lines = count_lines(fname);
	if (lines == -1)
		return ((char **)null_error("ERROR: The file does not exist"));
	map = malloc(sizeof(char *) * (lines + 1));
	if (!map)
		return ((char **)null_error("ERROR: malloc"));
	fd = open(fname, O_RDONLY);
	if (fd < 1)
		return ((char **)null_error("ERROR: The file does not exist"));
	line = 0;
	map[line] = get_next_line(fd);
	while (++line < lines - 1)
		map[line] = get_next_line(fd);
	map[line] = NULL;
	close(fd);
	return (map);
}
