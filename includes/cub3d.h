/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tde-nico <tde-nico@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 11:51:34 by tde-nico          #+#    #+#             */
/*   Updated: 2022/09/06 12:09:14 by tde-nico         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../libft/libft.h"
# include "../mlx/mlx.h"
# include "fcntl.h"

typedef struct s_game
{
	char	**map;
}	t_game;

//args_check
int		check_args(int argc, char **argv);

//error
char	*null_error(char *str);

//free
int		free_matrix(char **matrix);

//get_next_line
char	*get_next_line(int fd);

//map_read
char	**read_map(char *fname);

//str_utils
char	*ft_charjoin(char *s1, char s2);

#endif