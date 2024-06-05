/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luvallee <luvallee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 12:40:27 by luvallee          #+#    #+#             */
/*   Updated: 2024/02/24 12:06:44 by luvallee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stddef.h>
# include <stdlib.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 5
# endif

typedef struct s_list_gnl
{
	char				content;
	struct s_list_gnl	*next;
}						t_list_gnl;

# ifndef T_ELEMENT
#  define T_ELEMENT

typedef struct s_element
{
	size_t				count;
	char				*str;
	char				*buffer;
}						t_element;
# endif

char					*get_next_line(int fd);
int						check_endline(t_list_gnl **save);
char					*extract_string(t_list_gnl *save);
void					delete_and_free(t_list_gnl **save);
void					ft_add_back(t_list_gnl **lst, char data);
int						ft_get_size(t_list_gnl *lst);
t_list_gnl				*save_the_buffer(char *buffer, t_list_gnl **save);

#endif