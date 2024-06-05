/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_path_finding.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luvallee <luvallee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 14:37:49 by luvallee          #+#    #+#             */
/*   Updated: 2024/03/09 14:09:00 by luvallee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

/* Returns the position according to movement */
int	search_adjacents_nodes(char *map, int pos, t_move move, t_data *data)
{
	int	len;

	if (map[pos] == '\n')
		return (-1);
	len = data->column_nb - 1;
	if (move == up && pos > len)
		return (pos - len - 1);
	else if (move == down && pos < (int)(len * data->line_nb))
		return (pos + len + 1);
	else if (move == right && map[pos + 1] != '\0' && map[pos + 1] != '\n')
		return (pos + 1);
	else if (move == left && map[pos - 1] != '\0' && map[pos - 1] != '\n')
		return (pos - 1);
	return (-1);
}

/* Looking for a valid path = collect every items and access to the exit */
int	browse_the_map(char *map, int x, t_data *data, t_move move)
{
	int	result;

	if (map[x] == 'C')
		data->count--;
	if (map[x] == 'E')
		data->count--;
	if (map[x] == '1')
		return (INVALID);
	map[x] = '1';
	result = search_adjacents_nodes(map, x, down, data);
	if (map[result] != '1' && result != -1)
		browse_the_map(map, result, data, move);
	result = search_adjacents_nodes(map, x, right, data);
	if (map[result] != '1' && result != -1)
		browse_the_map(map, result, data, move);
	result = search_adjacents_nodes(map, x, left, data);
	if (map[result] != '1' && result != -1)
		browse_the_map(map, result, data, move);
	result = search_adjacents_nodes(map, x, up, data);
	if (map[result] != '1' && result != -1)
		browse_the_map(map, result, data, move);
	if (data->count == 0)
		return (VALID);
	else
		return (INVALID);
}

/* Returns the index of the Player Position "P" */
int	get_player_position(char *map, t_data *data)
{
	int	i;
	int	x;
	int	y;

	i = 0;
	x = 0;
	y = 0;
	while (map[i] != '\0')
	{
		if (y != data->start_y)
		{
			if (map[i] == '\n')
			{
				y++;
				x = 0;
			}
		}
		else if (y == data->start_y && x == data->start_x)
			return (i + 1);
		x++;
		i++;
	}
	return (i);
}

/* If we can't find a path, the map is not valid */
int	find_path(t_map **map, t_game *game, t_data *data)
{
	t_move	move;
	t_map	*map_lst;
	char	*map_str;

	move = down;
	map_lst = *map;
	map_str = copy_the_map(map_lst);
	data->count = data->collectables + data->exit;
	game->pos = get_player_position(map_str, data);
	if (browse_the_map(map_str, game->pos, data, move) != VALID)
		return (free(map_str), print_msg(7, 0), INVALID);
	free(map_str);
	return (VALID);
}
