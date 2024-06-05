/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luvallee <luvallee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 11:01:40 by luvallee          #+#    #+#             */
/*   Updated: 2024/03/13 12:18:32 by luvallee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

/* Stores every images in tab of pointers */
void	store_img(t_game *game, t_size s)
{
	void	*mlx;

	s.w = 0;
	s.h = 0;
	mlx = game->mlx;
	game->img[0] = mlx_xpm_file_to_image(mlx, "./img/collect.xpm", &s.w, &s.h);
	malloc_protection(game->img[0], game, "store_img=0");
	game->img[1] = mlx_xpm_file_to_image(mlx, "./img/collec_f.xpm", &s.w, &s.h);
	malloc_protection(game->img[1], game, "store_img=1");
	game->img[2] = mlx_xpm_file_to_image(mlx, "./img/exit.xpm", &s.w, &s.h);
	malloc_protection(game->img[2], game, "store_img=2");
	game->img[3] = mlx_xpm_file_to_image(mlx, "./img/exit_f.xpm", &s.w, &s.h);
	malloc_protection(game->img[3], game, "store_img=3");
	game->img[4] = mlx_xpm_file_to_image(mlx, "./img/player_f.xpm", &s.w, &s.h);
	malloc_protection(game->img[4], game, "store_img=4");
	game->img[5] = mlx_xpm_file_to_image(mlx, "./img/player.xpm", &s.w, &s.h);
	malloc_protection(game->img[5], game, "store_img=5");
	game->img[6] = mlx_xpm_file_to_image(mlx, "./img/water.xpm", &s.w, &s.h);
	malloc_protection(game->img[6], game, "store_img=6");
	game->img[7] = mlx_xpm_file_to_image(mlx, "./img/water_f.xpm", &s.w, &s.h);
	malloc_protection(game->img[7], game, "store_img=7");
	game->img[8] = mlx_xpm_file_to_image(mlx, "./img/wall.xpm", &s.w, &s.h);
	malloc_protection(game->img[8], game, "store_img=8");
}

void	ft_put_img_on_win(t_game *game, int n, int x, int y)
{
	mlx_put_image_to_window(game->mlx, game->win, game->img[n], x, y);
}

/* According to the value of the map, display images */
void	manage_img_conditions(t_game *game, int i, int up)
{
	if (game->map_p[i] == '1')
		ft_put_img_on_win(game, 8, (game->x - 1) * PX, game->y * PX);
	if (game->map_p[i] == '0' && game->map_p[up] == '1')
		ft_put_img_on_win(game, 7, (game->x - 1) * PX, game->y * PX);
	else if (game->map_p[i] == '0')
		ft_put_img_on_win(game, 6, (game->x - 1) * PX, game->y * PX);
	if (game->map_p[i] == 'E')
		ft_put_img_on_win(game, 2, (game->x - 1) * PX, game->y * PX);
	if (game->map_p[i] == 'C' && game->map_p[up] == '1')
		ft_put_img_on_win(game, 1, (game->x - 1) * PX, game->y * PX);
	else if (game->map_p[i] == 'C')
		ft_put_img_on_win(game, 0, (game->x - 1) * PX, game->y * PX);
	if (game->map_p[i] == 'P' && game->map_p[up] == '1')
		ft_put_img_on_win(game, 4, (game->x - 1) * PX, game->y * PX);
	else if (game->map_p[i] == 'P')
		ft_put_img_on_win(game, 5, (game->x - 1) * PX, game->y * PX);
	else if (game->map_p[i] == 'e')
		ft_put_img_on_win(game, 3, (game->x - 1) * PX, game->y * PX);
}

/* Loop in the map to display images */
int	display_game(t_game *game)
{
	int		i;
	int		res;
	t_move	move;

	game->y = 0;
	i = 0;
	move = up;
	while (game->map_p[i] != '\0')
	{
		if (game->map_p[i] == '\n')
		{
			game->x = 0;
			game->y++;
		}
		res = search_adjacents_nodes(game->map_p, i, move, game->data);
		manage_img_conditions(game, i, res);
		game->x++;
		i++;
	}
	return (0);
}

/* Initialization of mlx functions and loop in the window waiting for
hooks/input from the player */
void	so_long(t_game *game, t_data *data)
{
	t_size	size;
	t_move	move;

	size.w = PX * (data->column_nb - 1);
	size.h = PX * data->line_nb;
	move = up;
	game->data = data;
	game->data->count = 0;
	game->mlx = mlx_init();
	malloc_protection(game->mlx, game, "so_long=mlx");
	game->win = mlx_new_window(game->mlx, size.w, size.h, "so_long");
	malloc_protection(game->win, game, "so_long=win");
	store_img(game, size);
	mlx_loop_hook(game->mlx, display_game, game);
	mlx_hook(game->win, KeyRelease, KeyReleaseMask, &handle_input, game);
	mlx_hook(game->win, 17, 0, &complete_destroy, game);
	mlx_loop(game->mlx);
}
