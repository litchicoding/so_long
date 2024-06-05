/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luvallee <luvallee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 16:31:35 by luvallee          #+#    #+#             */
/*   Updated: 2024/03/13 12:14:51 by luvallee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include "../get_next_line/get_next_line.h"
# include "../libft/libft.h"
# include "../mlx/mlx.h"
# include <X11/X.h>
# include <X11/keysym.h>
# include <fcntl.h>
# include <stdlib.h>
# include <sys/stat.h>

# define VALID 0
# define INVALID 1
# define PX 64

typedef enum e_move
{
	up,
	down,
	left,
	right
}					t_move;

# ifndef T_MAP
#  define T_MAP

typedef struct s_map
{
	char			*content;
	struct s_map	*next;
}					t_map;
# endif

# ifndef T_SIZE
#  define T_SIZE

typedef struct s_size
{
	int				w;
	int				h;
}					t_size;
# endif

# ifndef T_DATA
#  define T_DATA

typedef struct s_data
{
	int				collectables;
	int				exit;
	int				start;
	int				start_x;
	int				start_y;
	size_t			line_nb;
	size_t			column_nb;
	int				count;
}					t_data;
# endif

# ifndef T_GAME
#  define T_GAME

typedef struct s_game
{
	int				fd;
	int				x;
	int				y;
	int				pos;
	void			*mlx;
	void			*win;
	void			*img[9];
	char			*map_p;
	struct s_data	*data;
}					t_game;
# endif

int					main(int argc, char *argv[]);
t_map				*store_the_map(t_map *map, int fd);
char				*copy_the_map(t_map *map);
int					checking_map_validity(t_map **map, t_data *data);
int					check_map_format(t_map **map, t_data *data);
int					is_map_enclosed(t_map **map);
int					find_path(t_map **map, t_game *game, t_data *data);
int					browse_the_map(char *map, int x, t_data *data, t_move move);
int					map_parsing(char cell, t_data *data, int index,
						int node_index);
int					search_adjacents_nodes(char *map, int pos, t_move move,
						t_data *data);
void				init_data(t_data *data, t_game *game);
void				print_msg(int nb, char *msg);
void				malloc_protection(void *var, t_game *game, char *msg);
int					complete_destroy(t_game *game);
void				free_the_list(t_map **lst);
void				destroy(t_game *game, t_map **map);
void				so_long(t_game *game, t_data *data);
int					handle_input(int keysym, t_game *game);
void				store_img(t_game *game, t_size s);
void				ft_put_img_on_win(t_game *game, int n, int x, int y);
int					display_game(t_game *game);
void				delete_img(t_game *game);

#endif