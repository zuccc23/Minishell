/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdodevsk <mdodevsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 13:34:24 by mdodevsk          #+#    #+#             */
/*   Updated: 2024/10/29 13:34:24 by mdodevsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*ustr;
	unsigned char	uc;
	size_t			i;

	i = 0;
	ustr = (unsigned char *)s;
	uc = (unsigned char)c;
	while (i < n)
	{
		if (ustr[i] == uc)
			return ((void *) &ustr[i]);
		i++;
	}
	return (NULL);
}
/*
int main(void)
{
    char *str = "mario";
    char *strr = "mario";
    int c = 95;
    ft_memchr(str, c, 3);
    memchr(strr, c, 3);
    return (0);
}*/