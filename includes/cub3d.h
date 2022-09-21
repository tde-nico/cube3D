/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tde-nico <tde-nico@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 11:51:34 by tde-nico          #+#    #+#             */
/*   Updated: 2022/09/08 12:39:48 by tde-nico         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../libs/libft/libft.h"
# include "../libs/mlx/mlx.h"
# include "../libs/mlx_linux/mlx.h"
# include <fcntl.h>
# include <math.h>

// Bonus
# include <sys/time.h>
# include <stdio.h>

// MLX Events
# define ON_KEYDOWN 2
# define ON_KEYUP 3
# define ON_MOUSEDOWN 4
# define ON_MOUSEUP 5
# define ON_MOUSEMOVE 6
# define ON_EXPOSE 12
# define ON_DESTROY 17

// MLX Keys
# define K_Q 12
# define K_W 13
# define K_E 14
# define K_R 15
# define K_T 17
# define K_Y 16
# define K_U 32
# define K_I 34
# define K_O 31
# define K_P 35
# define K_A 0
# define K_S 1
# define K_D 2
# define K_F 3
# define K_G 5
# define K_H 4
# define K_J 38
# define K_K 40
# define K_L 37
# define K_Z 6
# define K_X 7
# define K_C 8
# define K_V 9
# define K_B 11
# define K_N 45
# define K_M 46
# define K_ESCAPE 53
# define K_ENTER 36
# define K_BACKSPACE 51

// MLX Colors
# define RGB_RED 0x00FF0000
# define RGB_GREEN 0x0000FF00
# define RGB_BLUE 0x000000FF
# define RGB_WHITE 0x00FFFFFF
# define RGB_YELLOW 0x00FFFF00

# define MAP_CHARACTERS " 01NSWE"
# define PLAYER_CHARACTERS "NSWE"
# define NORD_TEXTURE "NO"
# define SUD_TEXTURE "SO"
# define WEST_TEXTURE "WE"
# define EAST_TEXTURE "EA"
# define FLOOR_COLOR "F"
# define CEILLING_COLOR "C"

// "map_init" for map intitalizaiton
// "inputs" for the input keys
# define VERBOSE ""
# define INVALID_TESTING 0
# define NAME "cub3D"
# define WIDTH 1280
# define HEIGHT 720
# define MINIMAP_TILE_SIZE 5
# define PLAYER_FOV 0.66
# define PLAYER_SPEED 5.0
# define PLAYER_ROTATION_SPEED 3.0

typedef struct s_vec2
{
	double	x;
	double	y;
}	t_vec2;

typedef struct s_map
{
	int		search_start;
	char	*nord;
	char	*sud;
	char	*west;
	char	*east;
	int		floor_color[3];
	int		ceilling_color[3];
	t_vec2	player_pos;
	char	**map;
	int		width;
	int		height;
}	t_map;

typedef struct s_player
{
	t_vec2	pos;
	t_vec2	dir;
	t_vec2	mov_dir;
	double	rot_dir;
	t_vec2	plane;
	t_vec2	mov_speed;
	double	rot_speed;
}	t_player;

typedef struct s_raycaster
{
	double	camera_x;
	t_vec2	ray_dir;
	int		map_x;
	int		map_y;
	t_vec2	side_dist;
	t_vec2	delta_dist;
	int		hit;
	int		step_x;
	int		step_y;
	int		side;
	double	perp_wall_dist;
	int		line_height;
	t_vec2	draw_start;
	t_vec2	draw_end;
	int		color;
}	t_raycaster;

typedef struct s_game
{
	void		*mlx;
	void		*win;
	t_map		*map;
	void		*walls[4];
	int			wall_widths[4];
	int			wall_heights[4];
	t_player	player;
	//double		time;
	//double		old_time;
	double		frame_time;
	t_raycaster	ray;
}	t_game;

//args_check
int		check_args(int argc, char **argv);

//debug
void	print_matrix(char **matrix);
void	print_map(t_map *map);

//error
char	*null_error(char *str);
t_map	*map_error(t_map *map, char **file, char *str);

//free
int		free_matrix(char **matrix);
int		free_map_textures(t_map *map);
int		free_map(t_map *map);
int		free_game(t_game *game);

//init
void	init_game(t_game *game);

//input
int		input_handler_down(int key, t_game *game);
int		input_handler_up(int key, t_game *game);
int		mouse_handler(int x, int y, t_game *game);

//main
int		clean_exit(t_game *game);
int		exit_game(void);

//map_read
t_map	*read_map(char *fname);

//map_valid
int		validate_map(t_map *map);

//read_file
char	**read_file(char *fname);

//start
void	start_game(t_game *game);

//str_utils
char	*ft_charjoin(char *s1, char s2);
char	**ft_arrdup(char **src);

//time
//double	get_ticks(void);

//update
int		update(t_game *game);

#endif
