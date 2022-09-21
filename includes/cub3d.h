/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tde-nico <tde-nico@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 11:51:34 by tde-nico          #+#    #+#             */
/*   Updated: 2022/09/07 13:01:28 by tde-nico         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../libft/libft.h"
# include "../mlx/mlx.h"
# include "fcntl.h"
# include "math.h"

# define MAP_CHARACTERS " 01NSEW"
# define NORD_TEXTURE "NO"
# define SUD_TEXTURE "SO"
# define WEST_TEXTURE "WE"
# define EAST_TEXTURE "EA"
# define FLOOR_COLOR "F"
# define CEILLING_COLOR "C"

// "map_init" for map intitalizaiton
# define VERBOSE "map_init"
# define NAME "cub3D"
# define WIDTH 1280
# define HEIGHT 720
# define MINIMAP_TILE_SIZE 5

typedef struct s_vec2
{
	float	x;
	float	y;
}	t_vec2;

typedef struct s_map
{
	char	*nord;
	char	*sud;
	char	*west;
	char	*east;
	int		floor_color[3];
	int		ceilling_color[3];
	char	**map;
	int		width;
	int		height;
}	t_map;

typedef struct s_minimap
{
	void	*map;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_minimap;

typedef struct s_game
{
	void		*mlx;
	void		*win;
	t_map		*map;
	t_minimap	minimap;
}	t_game;

//args_check
int		check_args(int argc, char **argv);

//colors
int		create_trgb(int t, int r, int g, int b);
int		get_t(int trgb);
int		get_r(int trgb);
int		get_g(int trgb);
int		get_b(int trgb);

//debug
void	print_matrix(char **matrix);
void	print_map(t_map *map);

//error
char	*null_error(char *str);

//free
int		free_matrix(char **matrix);
int		free_map_textures(t_map *map);
int		free_map(t_map *map);
int		free_game(t_game *game);

//init
void	init_game(t_game *game);

//main
int		clean_exit(t_game *game);
int		exit_game(void);

//mlx_images
void	my_mlx_pixel_put(t_minimap *minimap, int x, int y, int color);

//map_read
t_map	*read_map(char *fname);

//map_valid
int		validate_map(t_map *map);

//read_file
char	**read_file(char *fname);

//str_utils
char	*ft_charjoin(char *s1, char s2);
char	**ft_arrdup(char **src);

#endif