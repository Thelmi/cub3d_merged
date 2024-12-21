/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thelmy <thelmy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 19:51:59 by thelmy            #+#    #+#             */
/*   Updated: 2024/12/21 22:51:23 by thelmy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "./minilibx/mlx.h"
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <math.h>
# include <limits.h>
# include "./get_next_line/get_next_line.h"

# define WIDTH 1500
# define HEIGHT 1000
# define FOV_ANGLE (M_PI/3) 
# define TILE_SIZE 30 

typedef struct s_wall
{
	int start_y;
	int end_y;
	int wallslice_height;
	double texture_step;
	double tex_x;
	double tex_y;
	int	step_x;
	int	step_y;
	int	a;
	int	b;
} t_wall;

typedef struct s_ray
{
	double 	ray_angle;
	double 	ray_length;
	double 	ray_init_x;
	double 	ray_init_y;
	double 	c_per_unit_x;
	double 	c_per_unit_y;
	double 	first_hor_int_c;
	double 	first_ver_int_c;
    int 	hit_orientation;
}t_ray;

typedef struct s_img
{
	void *img;
	char *adrs;
	int	 bitsperpixel;
	int	 linelen;
	int	 endian;
}t_img;

typedef struct s_game
{
	void	*mlx_connection;
	void	*mlx_window;
	t_img	img;
	char	**map;
	char	**copy;
	char	*no;
	char	*so;
	char	*we;
	char	*ea;
	int		floor_hex;
	int		flr_r;
	int		flr_g;
	int		flr_b;
	int		ceil_hex;
	int		cl_r;
	int		cl_g;
	int		cl_b;
	char	pl_view;
	double	pl_view_ang;
	int		pl_x;
	int		pl_y;
	int 	pl_x_tile;
	int 	pl_y_tile;
	t_ray	ray;
	t_img 	north_texture;
    t_img 	south_texture;
    t_img 	east_texture;
    t_img 	west_texture;
	t_wall	wall;
	int		free_flag;
	int		newline;
}			t_game;

t_game		locate_check_players(char **arr, t_game game, int fd, char *read);
char		*t_strjoin(char *s1, char *s2);
t_game		map_parsing(t_game game, int fd);
t_game		parsing(t_game game, int ac, char **av);
t_game		map_file_parsing(t_game game, int fd);
int			t_strncmp(char *s1, char *s2, size_t n);
size_t		t_strlen(char *str);
size_t		ft_strlcpy(char *dst, char *src, size_t dstsize);
t_game		textures_parsing(char *line, t_game game, int fd);
char		*ft_strdup(char *s1);
void		free_textures(t_game game);
t_game		assigning_floor_color(char *line, t_game game, int fd);
int			ft_isdigit(int c);
t_game		parse_rgb(char *line, t_game game);
int			ft_atoi(char *str);
int			invalid_rgb(char *line, t_game game, int fd);
void		check_last_characters(char *line, t_game *game, int i);
t_game		assigning_fl_rgb(t_game game, int *values);
int			parse_single_value(char *line, int *i, t_game *game);
int			commas_couter(char *line);
int			is_valid_char(char c);
t_game		assigning_ceil_color(char *line, t_game game, int fd);
void		letters_checker(char *read_next, char *read, t_game game, int fd);
void		valid_all_ones(char *read, t_game game, int fd);
void		free_and_exit(char **str, int fd, t_game game, char *read);
char		*ft_substr(char *s, unsigned int start, size_t len);
char		**ft_split(char *s, char c);
void		free_map(t_game game);
int			is_enclosed(t_game game);
void		letters_exit(char *read_next, char *read, t_game game, int fd);
void		last_line_valid(char *read_next, char *read, t_game game, int fd);
int			is_whitespaces(char c);
void		free_textures_exit(char *line, t_game game, int fd);
int			key_hook(int keycode, t_game *game);
void 		draw(t_game *game);
void		init_player_view_and_position(t_game *game);
void		init_ray_values(t_game *game);
void		init_walls(t_game *game);
void		draw_walls(t_game *game);
void		get_we_textures(t_game *game);
void		get_ns_textures(t_game *game);
void		draw_wall_slice(t_game *game, int x_screen);
#endif