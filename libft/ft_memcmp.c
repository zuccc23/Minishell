/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdodevsk <mdodevsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 13:36:27 by mdodevsk          #+#    #+#             */
/*   Updated: 2024/10/29 13:36:27 by mdodevsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t			i;
	unsigned char	*us1;
	unsigned char	*us2;

	us1 = (unsigned char *)s1;
	us2 = (unsigned char *)s2;
	i = 0;
	while (i < n)
	{
		if (us1[i] != us2[i])
			return ((unsigned char) us1[i] - (unsigned char) us2[i]);
		i++;
	}
	return (0);
}
/*
int main (void)
{
    char *str = "mario";
    char *strr = "";
    size_t c = 2;
    printf("%d\n", ft_memcmp(str, strr, c));
    printf("%d\n", memcmp(str, strr, c));
    return (0);
}*/
