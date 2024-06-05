/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luvallee <luvallee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 12:06:48 by luvallee          #+#    #+#             */
/*   Updated: 2024/03/13 12:15:51 by luvallee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

void	print_msg(int nb, char *msg)
{
	if (nb == 1)
		ft_printf("Error->Too many or missing (map) argument\n");
	else if (nb == 2)
		ft_printf("Error->Cannot open fd\n");
	else if (nb == 3)
		ft_printf("Error->The map is not rectangular\n");
	else if (nb == 4)
		ft_printf("Error->The map is not surrounded by walls\n");
	else if (nb == 5)
		ft_printf("Error->Components aren't valid (only P=1/E=1/C>0 + 0&1)\n");
	else if (nb == 6)
		ft_printf("Error->Not enough or too many components (P=1/E=1/C>0)\n");
	else if (nb == 7)
	{
		ft_printf("Error->The map cannot be solved, do you respect the rules?");
		ft_printf(" Need to access the exit AND find all collectables\n");
	}
	else if (nb == 8)
		ft_printf("Error->Problem during allocation : %s\n", msg);
	else if (nb == 9)
		ft_printf("YOU WIN! So looong! And thanks for all the water lilies!\n");
	else if (nb == 10)
		ft_printf("Error->The map is invalid, the game stops here\n");
	else if (nb == 11)
		ft_printf("Error->Wrong extension filename, must be '.ber'\n");
}

/* Initialize all the variables of every structures */
void	init_data(t_data *data, t_game *game)
{
	data->collectables = 0;
	data->exit = 0;
	data->start = 0;
	data->start_x = 0;
	data->start_y = 0;
	data->line_nb = 0;
	data->column_nb = 0;
	data->count = 0;
	game->fd = 0;
	game->x = 1;
	game->y = 0;
	game->mlx = NULL;
	game->win = NULL;
	game->map_p = NULL;
	game->img[0] = 0;
	game->img[1] = 0;
	game->img[2] = 0;
	game->img[3] = 0;
	game->img[4] = 0;
	game->img[5] = 0;
	game->img[6] = 0;
	game->img[7] = 0;
	game->img[8] = 0;
}

/* Copy the linked list (old map) to a string (new map) */
char	*copy_the_map(t_map *map)
{
	char	*temp;
	int		len;
	int		i;
	int		j;

	len = ft_strlen(map->content);
	temp = malloc(sizeof(char) * ((len * ft_lstsize(map)) + 1));
	if (!temp)
		return (print_msg(8, "copy_map=tmp"), NULL);
	j = 0;
	while (map != NULL)
	{
		i = 0;
		while (map->content[i] != '\0')
		{
			temp[j] = map->content[i];
			i++;
			j++;
		}
		map = map->next;
	}
	temp[j++] = '\n';
	temp[j] = '\0';
	return (temp);
}

/* In case of allocation failure clean everything */
void	malloc_protection(void *var, t_game *game, char *msg)
{
	if ((!var) || (var == 0))
	{
		print_msg(8, msg);
		delete_img(game);
		complete_destroy(game);
		exit(1);
	}
}
