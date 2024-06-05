/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luvallee <luvallee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 19:17:33 by luvallee          #+#    #+#             */
/*   Updated: 2024/02/22 12:19:52 by luvallee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	ft_add_back(t_list_gnl **lst, char data)
{
	t_list_gnl	*new;
	t_list_gnl	*last;

	new = malloc(sizeof(t_list_gnl));
	if (!new)
		return ;
	new->content = data;
	last = *lst;
	new->next = NULL;
	if (!lst)
	{
		*lst = new;
		return ;
	}
	while (last->next != NULL)
		last = last->next;
	last->next = new;
}

int	ft_get_size(t_list_gnl *lst)
{
	int	i;

	i = 0;
	while (lst)
	{
		i++;
		lst = lst->next;
	}
	return (i);
}
