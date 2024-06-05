/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luvallee <luvallee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 12:03:40 by luvallee          #+#    #+#             */
/*   Updated: 2024/03/04 18:06:18 by luvallee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include "../include/so_long.h"
# include <stdarg.h>
# include <stddef.h>
# include <stdlib.h>
# include <unistd.h>

// typedef struct s_list
// {
// 	void			*content;
// 	struct s_list	*next;
// }					t_map;

# ifndef T_MAP
#  define T_MAP
typedef struct s_map
{
	char			*content;
	struct s_map	*next;
}					t_map;
# endif

int					ft_strlen(const char *str);

void				ft_lstadd_front(t_map **lst, t_map *new);
// int					ft_lstsize(t_map *lst);
t_map				*ft_lstlast(t_map *lst);
void				ft_lstadd_node_back(t_map **lst, t_map *new);
int					ft_lstsize(t_map *lst);
int					ft_printf(const char *format, ...);
int					ft_printf_char(int c);
int					ft_printf_string(char *str);
int					ft_printf_digit(long long nb, int base, char specifier);
int					ft_printf_adress(unsigned long long pointer);
char				*ft_itoa(int n);
char				*ft_strnstr(const char *big, const char *little,
						size_t len);
#endif /* !LIBFT_H */
