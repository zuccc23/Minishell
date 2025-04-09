/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdodevsk <mdodevsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 08:35:20 by mdodevsk          #+#    #+#             */
/*   Updated: 2024/11/13 15:23:54 by mdodevsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	if (n <= 0)
		return (0);
	while (s1[i] != '\0' && i < n - 1)
	{
		if (s1[i] != s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}
/*
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
int	main(int ac, char **av)
{
	if (ac > 1)
	{
		printf("%d \n", ft_strncmp(av[1], av[2], atoi(av[3])));
		printf("%d \n", strncmp(av[1], av[2], atoi(av[3])));
	}
	else
		printf("ya rien");
	return (0);
}*/
