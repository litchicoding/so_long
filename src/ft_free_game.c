/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_game.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luvallee <luvallee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 12:04:38 by luvallee          #+#    #+#             */
/*   Updated: 2024/03/13 12:19:03 by luvallee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

/* Frees every nodes and their contents */
void	free_the_list(t_map **lst)
{
	t_map	*temp;

	if (!*lst)
		return ;
	while (*lst != NULL)
	{
		temp = (*lst)->next;
		free((*lst)->content);
		free(*lst);
		*lst = temp;
	}
}

void	delete_img(t_game *game)
{
	int	i;

	i = 0;
	while (game->img[i])
	{
		mlx_destroy_image(game->mlx, game->img[i]);
		i++;
	}
}

/* Frees and destroys var/pointers to end the game */
int	complete_destroy(t_game *game)
{
	if (game->img[0] && game->img[1] && game->img[2] && game->img[3]
		&& game->img[4] && game->img[5] && game->img[6] && game->img[7])
	{
		mlx_destroy_image(game->mlx, game->img[0]);
		mlx_destroy_image(game->mlx, game->img[1]);
		mlx_destroy_image(game->mlx, game->img[2]);
		mlx_destroy_image(game->mlx, game->img[3]);
		mlx_destroy_image(game->mlx, game->img[4]);
		mlx_destroy_image(game->mlx, game->img[5]);
		mlx_destroy_image(game->mlx, game->img[6]);
		mlx_destroy_image(game->mlx, game->img[7]);
		if (game->img[8])
			mlx_destroy_image(game->mlx, game->img[8]);
	}
	ft_printf("Your score is : %d\n", game->data->count);
	if (game->win)
		mlx_destroy_window(game->mlx, game->win);
	if (game->mlx)
		mlx_destroy_display(game->mlx);
	if (game->map_p)
		free(game->map_p);
	if (game->mlx)
		free(game->mlx);
	close(game->fd);
	exit(1);
}

/* If the map is invalid, simple free */
void	destroy(t_game *game, t_map **map)
{
	free_the_list(map);
	close(game->fd);
	exit(1);
}
