/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luvallee <luvallee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 16:31:57 by luvallee          #+#    #+#             */
/*   Updated: 2024/03/13 14:48:39 by luvallee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

int	main(int argc, char *argv[])
{
	t_game	game;
	t_data	data;
	t_map	*map;

	if (argc != 2)
		return (print_msg(2, 0), 1);
	init_data(&data, &game);
	map = NULL;
	game.fd = open(argv[1], O_RDONLY);
	if (game.fd == -1)
		return (print_msg(2, 0), -1);
	if (ft_strnstr(argv[1], ".ber", ft_strlen(argv[1])) == NULL)
		return (print_msg(11, 0), 1);
	map = store_the_map(map, game.fd);
	if (checking_map_validity(&map, &data) != VALID)
		return (destroy(&game, &map), print_msg(10, 0), INVALID);
	if (find_path(&map, &game, &data) != VALID)
		return (destroy(&game, &map), print_msg(10, 0), INVALID);
	game.map_p = copy_the_map(map);
	free_the_list(&map);
	ft_printf("Welcome, the frog must collect all the water lilies and find ");
	ft_printf("the exit as fast as possible, she hates when it's sooo long!\n");
	if (game.map_p != NULL)
		so_long(&game, &data);
	return (0);
}
