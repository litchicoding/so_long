/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_map_parsing.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luvallee <luvallee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 12:05:51 by luvallee          #+#    #+#             */
/*   Updated: 2024/03/13 11:19:13 by luvallee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

/* Store the map in a linked list */
t_map	*store_the_map(t_map *map, int fd)
{
	int		len;
	char	*temp;
	t_map	*new;

	temp = NULL;
	new = NULL;
	while (1)
	{
		temp = get_next_line(fd);
		if (temp == NULL)
			return (free(temp), map);
		len = ft_strlen(temp);
		new = malloc(sizeof(t_map));
		if (!new)
			return (print_msg(8, "store_the_map=new"), NULL);
		new->content = temp;
		new->next = NULL;
		ft_lstadd_node_back(&map, new);
	}
	return (map);
}

/* Parse the values of the map and check if the values are correct */
int	map_parsing(char cell, t_data *data, int index, int node_index)
{
	if (cell == 'C')
		data->collectables += 1;
	else if (cell == 'E')
		data->exit++;
	else if (cell == 'P')
	{
		data->start++;
		data->start_x = index;
		data->start_y = node_index;
	}
	else if (cell != '0' && cell != '1' && cell != '\n')
		return (print_msg(5, 0), INVALID);
	return (VALID);
}

/* Check if the map is surrounded by walls or not*/
int	is_map_enclosed(t_map **map)
{
	t_map	*head;
	t_map	*body;
	t_map	*last;
	int		j;
	int		i;

	head = (*map);
	body = head->next;
	last = ft_lstlast(*map);
	j = ft_strlen(body->content);
	i = 0;
	while (head->content[i] != '\n' && last->content[i] != '\0')
	{
		if (head->content[i] != '1' || last->content[i] != '1')
			return (print_msg(4, 0), INVALID);
		i++;
	}
	i = 0;
	while (body != NULL && body->content != last->content)
	{
		if (body->content[i] != '1' || body->content[j - 2] != '1')
			return (print_msg(4, 0), INVALID);
		body = body->next;
	}
	return (VALID);
}

/* Check if the map is rectangular */
int	check_map_format(t_map **map, t_data *data)
{
	t_map	*node;
	int		current_len;
	int		next_len;

	node = *map;
	while (node != NULL)
	{
		if (node->next == NULL)
			break ;
		current_len = ft_strlen(node->content);
		next_len = ft_strlen(node->next->content);
		node = node->next;
		if (node->next == NULL)
			next_len += 1;
		if (current_len != next_len)
			return (print_msg(3, 0), INVALID);
	}
	data->column_nb = current_len;
	return (VALID);
}

/* Analyzes the map to check that it is in the correct format and conforms
to the subject's requirements */
int	checking_map_validity(t_map **map, t_data *data)
{
	t_map	*node;
	int		i;

	if (!*map || !(*map)->next)
		return (INVALID);
	node = *map;
	data->line_nb = 0;
	while (node != NULL && check_map_format(map, data) != INVALID
		&& is_map_enclosed(map) != INVALID)
	{
		i = 0;
		while (node->content[i] != '\0')
		{
			if (map_parsing(node->content[i], data, i, data->line_nb) != VALID)
				return (INVALID);
			i++;
		}
		node = node->next;
		data->line_nb++;
	}
	if (data->collectables > 0 && data->exit == 1 && data->start == 1)
		return (VALID);
	else
		return (print_msg(6, 0), INVALID);
	return (INVALID);
}
