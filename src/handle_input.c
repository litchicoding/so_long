/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_input.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luvallee <luvallee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 13:00:23 by luvallee          #+#    #+#             */
/*   Updated: 2024/03/09 14:14:31 by luvallee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

/* Change the position and correspondant value int the map */
void	handle_move(t_game *game, int tmp)
{
	if (game->map_p[tmp] != '1')
	{
		if (game->map_p[tmp] == 'C')
			game->data->collectables--;
		if (game->map_p[tmp] == 'E')
		{
			if (game->data->exit == 1)
				game->data->exit--;
			game->map_p[tmp] = 'e';
		}
		else
			game->map_p[tmp] = 'P';
		if (game->map_p[game->pos] != 'e')
			game->map_p[game->pos] = '0';
		else
			game->map_p[game->pos] = 'E';
		game->pos = tmp;
		game->data->count++;
	}
	if ((game->data->collectables == 0 && game->data->exit == 0)
		&& (game->map_p[game->pos] == 'e' || game->map_p[game->pos] == 'E'))
	{
		print_msg(9, 0);
		complete_destroy(game);
	}
}

/* Manage the hooks/inputs and calls needed functions */
int	handle_input(int keysym, t_game *game)
{
	t_move	move;
	int		tmp;

	move = up;
	tmp = 0;
	if (keysym == XK_Escape)
	{
		complete_destroy(game);
		return (0);
	}
	else if (keysym == XK_w || keysym == XK_Up)
		tmp = search_adjacents_nodes(game->map_p, game->pos, up, game->data);
	else if (keysym == XK_s || keysym == XK_Down)
		tmp = search_adjacents_nodes(game->map_p, game->pos, down, game->data);
	else if (keysym == XK_d || keysym == XK_Right)
		tmp = search_adjacents_nodes(game->map_p, game->pos, right, game->data);
	else if (keysym == XK_a || keysym == XK_Left)
		tmp = search_adjacents_nodes(game->map_p, game->pos, left, game->data);
	handle_move(game, tmp);
	if (game->map_p[tmp] != '1')
		ft_printf("Moves : %d\n", game->data->count);
	return (0);
}
