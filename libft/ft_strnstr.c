/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luvallee <luvallee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 15:37:44 by luvallee          #+#    #+#             */
/*   Updated: 2023/11/22 13:45:48 by luvallee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	little_len;
	size_t	i;
	size_t	j;

	if ((big == NULL || little == NULL) && len == 0)
		return (0);
	little_len = ft_strlen(little);
	i = 0;
	if (little_len == 0)
		return ((char *)big);
	while (big[i] != '\0' && (i + little_len) <= len)
	{
		j = 0;
		while (little[j] != '\0' && big[i + j] == little[j])
			j++;
		if (little[j] == '\0')
			return ((char *)&big[i]);
		i++;
	}
	return (NULL);
}

/*Cherche la premiere occurence de la chaine 'little' au sein de la
chaine 'big' mais ne pas chercher plus loin que 'len' octets.
If little is empty, big is returned; if little occurs nowhere, null is
returned; otherwise a pointer to the first character of the first occurence
of little is returned. */

// #include <stdio.h>
// #include <string.h>
// int main()
// {
//     printf("%s \n",ft_strnstr("courgette", "courbette", 10));
//     printf("%s", strnstr("courgette", "courbette", 10));
//     return (0);
// }
