/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdodevsk <mdodevsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 23:38:23 by mdodevsk          #+#    #+#             */
/*   Updated: 2024/10/25 23:38:23 by mdodevsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	unsigned char	*uchar;
	size_t			i;

	i = 0;
	uchar = (unsigned char *) s;
	while (i < n)
	{
		uchar[i] = 0;
		i++;
	}
}
/*
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>
int	main(int ac, char **av)
{
	(void)ac;
	char str[] = "hello";
	char strr[] = "hello";
	ft_bzero(str, 8);
	bzero(strr, 8);
	printf("%s\n", str);
	printf("%s\n", strr);
	return (0);
}*/